%% Exercise 3.1
clear;clc;

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
syms a_z
syms b_z

Rab = [cos(a_z) -sin(a_z) 0; sin(a_z) cos(a_z) 0; 0 0 1]
Rbc = [cos(b_z) -sin(b_z) 0; sin(b_z) cos(b_z) 0; 0 0 1]
Rac = Rab*Rbc
%Trig idendity sin(a(+/-)b) = sin(a)cos(b) (+/-) cos(a)sin(b)
%Trig idendity cos(a(+/-)b) = cos(a)cos(b) (-/+) sin(a)sin(b)
simplify(Rac) 
%Proofs that multiplying rotationmatrix makes it possisble to rotate
%from one frame to another. 
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
Orth_Col = [dot(Rba(1,:),Rba(2,:)),dot(Rba(1,:),Rba(3,:)),dot(Rba(2,:),Rba(3,:))]
Length_Col = [norm(Rba(1,:)),norm(Rba(2,:)),norm(Rba(3,:))]

% Show that Transpose 
% If  exist VV^1 = I then must VV' = I exist. 
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
syms z
syms x
syms  y
y = -pi/2
Rrpy =[cos(z) -sin(z) 0; sin(z) cos(z) 0; 0 0 1]* [cos(y) 0 sin(y); 0 1 0; -sin(y) 0 cos(y)] * [1 0 0; 0 cos(x) -sin(x); 0 sin(x) cos(x)]
% Trig ident tan(x) = sin(x)/cos(x)
%We know angle y, we need to find angle x and z which can be found using
%the trig ident stated above with atan2(Rrpy_32,Rrpy_33).
atan2(Rrpy(3,2),Rrpy(3,3))
% den er i hånden
cos(y)
%% Exercise 3.5
clear; clc;
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

Tba = [ Rba,oB'-oA';
        0,0,0,1]
inTba
% Inverse

%           |           |             |
%           |   Rba'    |  -Rba'*oB   |-
%   Tba =   |-------------------------|
%           |  0  0  0  |      1      |
%           |           |             |

Tab = [ Rba',-Rba'*oB'-oA';
        0,0,0,1]
% ii    
% %Rcb = [ dot(xB,xC),dot(xB,yC),dot(xB,zC);
%         dot(yB,xC),dot(yB,yC),dot(yB,zC);
%         dot(zB,xC),dot(zB,yC),dot(zB,zC)];
%     
%Tcb = [ Rcb,oC';
%        0,0,0,1]

% iii
%Tca = Tba*Tcb




