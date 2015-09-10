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

% Exercise 3.2
d = dot()