#include <iostream>
#include <rw/rw.hpp>
#include <rwlibs/pathplanners/rrt/RRTPlanner.hpp>
#include <rwlibs/pathplanners/rrt/RRTQToQPlanner.hpp>
#include <rwlibs/proximitystrategies/ProximityStrategyFactory.hpp>

#include <tuple>
#include <vector>

#include <typeinfo>

#include <rw/pathplanning/PathAnalyzer.hpp>

#include <rw/kinematics/Kinematics.hpp>
#include <rw/kinematics/MovableFrame.hpp>
#include <rw/kinematics/Frame.hpp>
#include <rw/kinematics/State.hpp>


using namespace std;
using namespace rw::common;
using namespace rw::kinematics;
using namespace rw::loaders;
using namespace rw::models;
using namespace rw::pathplanning;
using namespace rw::proximity;
using namespace rw::trajectory;
using namespace rwlibs::pathplanners;
using namespace rwlibs::proximitystrategies;

#define MAXTIME 10.

bool checkCollisions(Device::Ptr device, const State &state, const CollisionDetector &detector, const Q &q) {
    State testState;
    CollisionDetector::QueryResult data;
    bool colFrom;

    testState = state;
    device->setQ(q,testState);
    colFrom = detector.inCollision(testState,&data);
    if (colFrom) {
        cerr << "Configuration in collision: " << q << endl;
        cerr << "Colliding frames: " << endl;
        FramePairSet fps = data.collidingFrames;
        for (FramePairSet::iterator it = fps.begin(); it != fps.end(); it++) {
            cerr << (*it).first->getName() << " " << (*it).second->getName() << endl;
        }
        return false;
    }
    return true;
}

tuple<double, double, double> pathPlannerFunc(double extend){

    const string wcFile = "/home/student/ROVI/Mand2/Kr16WallWorkCell/Scene.wc.xml";
    const string deviceName = "KukaKr16";
    const string bottle = "Bottle";

    Q from(6,-3.142,-0.827,-3.002,-3.143,0.099,-1.573);
    Q to(6,1.571,0.006,0.030,0.153,0.762,4.490);

    WorkCell::Ptr wc = WorkCellLoader::Factory::load(wcFile);
    Device::Ptr device = wc->findDevice(deviceName);

    rw::kinematics::Frame *deviceB = wc->findFrame(bottle);

    if (device == NULL) {
        cerr << "Device: " << deviceName << " not found!" << endl;
        exit(-1);
    }
    if (deviceB == NULL) {
        cerr << "Device: " << bottle << " not found!" << endl;
        exit(-1);
    }

    rw::kinematics::State state = wc->getDefaultState();

    device->setQ(from, state);
    Kinematics::gripFrame(deviceB,device->getEnd(),state);

    CollisionDetector detector(wc, ProximityStrategyFactory::makeDefaultCollisionStrategy());
    PlannerConstraint constraint = PlannerConstraint::make(&detector,device,state);

    QSampler::Ptr sampler = QSampler::makeConstrained(QSampler::makeUniform(device),constraint.getQConstraintPtr());
    QMetric::Ptr metric = MetricFactory::makeEuclidean<Q>();
    QToQPlanner::Ptr planner = RRTPlanner::makeQToQPlanner(constraint, sampler, metric, extend, RRTPlanner::RRTConnect);

    if (!checkCollisions(device, state, detector, from))
        exit(-1);
    if (!checkCollisions(device, state, detector, to))
        exit(-1);

    PathAnalyzer::CartesianAnalysis distance_traveled;
    double path_length = 0;

    PathAnalyzer path_analyse(device,state);

    QPath path;

    Timer t;
    t.resetAndResume();
    planner->query(from,to,path,MAXTIME);
    t.pause();
    distance_traveled = path_analyse.analyzeCartesian(path,deviceB);
    path_length += distance_traveled.length;

    cout << extend<< "\tPath of length " << path.size() << " found in " << t.getTime() << " seconds." << endl;
    if (t.getTime() >= MAXTIME) {
        cout << "Notice: max time of " << MAXTIME << " seconds reached." << endl;
    }

    for (QPath::iterator it = path.begin(); it < path.end(); it++) {
        cout << "set" << *it << endl;//"setQ" << bins.substr(3,bins.length()) << endl;
    }

    auto tmp = make_tuple(extend, path_length,t.getTime());

    return tmp;
}

int main(int argc, char** argv) {

    vector<tuple<double, double, double>> result;
    Math::seed();


    for(double i=0.1 ; i < 6.28 ; i += 0.01 ){
        result.push_back(pathPlannerFunc(i));
    }

    for ( const auto& i : result) {
        cout <<  get<0>(i) << ","  << get<1>(i) <<","<<get<2>(i) <<"\n";
    }

    return 0;
}
