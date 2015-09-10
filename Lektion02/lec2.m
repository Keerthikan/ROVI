clear;clc;

% Exercise 3.1
xA = [1,0,0];
yA = [0,0.866,0.5];
zA = [0,-0.5,0.866];

xB = [0,0.866,-0.5];
yB = [0,-0.5,-0.866];
zB = [1,0,0];

Rba = [dot(xA,xB),dot(xA,yB),dot(xA,zB);
    dot(yA,xB),dot(yA,yB),dot(yA,zB);
    dot(zA,xB),dot(zA,yB),dot(zA,zB)]

c1 = dot(Rba(1,:),Rba(2,:))
c2 = dot(Rba(1,:),Rba(3,:))
c3 = dot(Rba(2,:),Rba(3,:))

%% Exercise 3.2
clear;clc;

syms xA yA zA;
syms xB yB zB;
syms xC yC zC;

Rba = [ xA*xB,xA*yB,xA*zB;
        yA*xB,yA*yB,yA*zB;
        zA*xB,zA*yB,zA*zB]

Rcb = [ xB*xC,xB*yC,xB*zC;
        yB*xC,yB*yC,yB*zC;
        zB*xC,zB*yC,zB*zC]

Rca = [ xA*xC,xA*yC,xA*zC;
        yA*xC,yA*yC,yA*zC;
        zA*xC,zA*yC,zA*zC]

R = Rba*Rcb

%% Exercise 3.2
clear;clc;



%% Exercise 3.3
clear;clc;


xA = [1,0,0];
yA = [0,0.866,0.5];
zA = [0,-0.5,0.866];

xB = [0,0.866,-0.5];
yB = [0,-0.5,-0.866];
zB = [1,0,0];

Rba = [ dot(xA,xB),dot(xA,yB),dot(xA,zB);
        dot(yA,xB),dot(yA,yB),dot(yA,zB);
        dot(zA,xB),dot(zA,yB),dot(zA,zB)]

% Orthogonality, Colums    
OrthC = [dot(Rba(1,:),Rba(2,:)),dot(Rba(1,:),Rba(3,:)),dot(Rba(2,:),Rba(3,:))]
Lc = [norm(Rba(1,:)),norm(Rba(2,:)),norm(Rba(3,:))]

% Transpose
T = Rba*Rba'

% Orthogonality, Rows
OrthR = [dot(Rba(:,1),Rba(:,2)),dot(Rba(:,1),Rba(:,3)),dot(Rba(:,2),Rba(:,3))]
Lr = [norm(Rba(:,1)),norm(Rba(:,2)),norm(Rba(:,3))]

% Determinant
Dt = det(Rba)
[v,D] = eig(Rba)

%D(1,1)*D(2,2)*D(3,3)

%% Exercise 3.4
clear; clc;


phi_y = -(pi/2);











