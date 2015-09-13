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
syms a_z
syms b_z

Rab = [cos(a_z) -sin(a_z) 0; sin(a_z) cos(a_z) 0; 0 0 1]
Rbc = [cos(b_z) -sin(b_z) 0; sin(b_z) cos(b_z) 0; 0 0 1]
Rac = Rab*Rbc
%Trig idendity sin(a(+/-)b) = sin(a)cos(b) (+/-) cos(a)sin(b)
%Trig idendity cos(a(+/-)b) = cos(a)cos(b) (-/+) sin(a)sin(b)

simplify(Rac) 
% Proofs that the multiplying rotationmatrix makes it possisble to rotate
% from one frame to another. 
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

%% Exercise 3.5
clear; clc;

xA = [1,0,0];
yA = [0,0.866,0.5];
zA = [0,-0.5,0.866];

xB = [0,0.866,-0.5];
yB = [0,-0.5,-0.866];
zB = [-1,0,0];

xC = [0,1,0];
yC = [0,0,1];
zC = [1,0,0];

oA = [2,1,0];
oB = [4,4,1];
oC = [5,0,0];
 
% i 
Rba = [ dot(xA,xB),dot(xA,yB),dot(xA,zB);
        dot(yA,xB),dot(yA,yB),dot(yA,zB);
        dot(zA,xB),dot(zA,yB),dot(zA,zB)]

%           |           |        |
%           |   Rba     |   oB   |
%   Tba =   |--------------------|
%           |  0  0  0  |   1    |
%           |           |        |

Tba = [ Rba,oA';
        0,0,0,1]
    
% Inverse

%           |           |             |
%           |   Rba'    |  -Rba'*oB   |
%   Tba =   |-------------------------|
%           |  0  0  0  |      1      |
%           |           |             |

Tab = [ Rba',-Rba'*oB';
        0,0,0,1]
% ii    
Rcb = [ dot(xB,xC),dot(xB,yC),dot(xB,zC);
        dot(yB,xC),dot(yB,yC),dot(yB,zC);
        dot(zB,xC),dot(zB,yC),dot(zB,zC)];
    
Tcb = [ Rcb,oC';
        0,0,0,1]

% iii
Tca = Tba*Tcb









