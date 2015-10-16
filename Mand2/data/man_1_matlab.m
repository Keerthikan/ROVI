clc;clear;

extend_1 = csvread('ext1.csv');
extend_2 = csvread('ext2.csv');
extend_3 = csvread('ext3.csv');
extend_4 = csvread('ext4.csv');
extend_5 = csvread('ext5.csv');
extend_6 = csvread('ext6.csv');
extend_7 = csvread('ext7.csv');
extend_8 = csvread('ext8.csv');
extend_9 = csvread('ext9.csv');
extend_0 = csvread('ext0.csv');

extend_var = extend_1(:,1);

time = [extend_1(:,3) extend_2(:,3) extend_3(:,3) extend_4(:,3) extend_5(:,3) extend_6(:,3) extend_7(:,3) extend_8(:,3) extend_9(:,3) extend_0(:,3)];

path_size = [extend_1(:,2) extend_2(:,2) extend_3(:,2) extend_4(:,2) extend_5(:,2) extend_6(:,2) extend_7(:,2) extend_8(:,2) extend_9(:,2) extend_0(:,2)];

time_ave = mean(time.')';
path_size = mean(path_size.')';

figure(1)
[ax h1 h2] = plotyy(extend_var, path_size, extend_var, time_ave);
rectangle('Position', [0.8, -2, 1, 190], 'LineStyle', '--', 'EdgeColor', 'r');

xlabel('Epsilon variable');
axes(ax(1)); ylabel('Path size in N');
axes(ax(2)); ylabel('Planning time in sec');
legend('Planning time', 'Path size');
title('Estimation of epsilon')
