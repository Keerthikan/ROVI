clear;clc;

syms x_a
syms x_b
syms x_c
syms y_a
syms y_b
syms y_c
syms z_a
syms z_b
syms z_c

% Exercise 3.1
xA = [1,0,0];
yA = [0,sqrt(3)/2,0.5];
zA = [0,-0.5,-sqrt(3)/2];

xB = [0,sqrt(3)/2,-0.5];
yB = [0,-0.5,-sqrt(3)/2];
zB = [1,0,0];

Rba = [dot(xA,xB),dot(xA,yB),dot(xA,zB);
    dot(yA,xB),dot(yA,yB),dot(yA,zB);
    dot(zA,xB),dot(zA,yB),dot(zA,zB)];

Rba(2,:)
