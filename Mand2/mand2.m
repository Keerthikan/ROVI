clc;clear;

m = csvread('result.csv');

time = m(1,:);

plot(m(:,1),m(:,2),'r', m(:,1),m(:,3),'b')
