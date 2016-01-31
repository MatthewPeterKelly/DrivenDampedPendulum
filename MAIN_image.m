% MAIN.m  --  Construct an image of the fractal basin of attraction for the
%             Driven Damped Pendulum
%

clc; clear;


% Specify the initial search grid
q = linspace(-pi,pi,70);  %Angles
w = linspace(-5,5,50);  %Rates

% Expand out to a grid:
[qq, ww] = meshgrid(q,w);
Q0 = reshape(qq,1,numel(qq));
W0 = reshape(ww,1,numel(ww));
Z0 = [Q0;W0];

% Dynamical system - driven damped pendulum
dynSys = @(t,z)( [z(2,:);  cos(t) - 0.1*z(2,:) - sin(z(1,:))] );

nBasinTrack = 11;  %Only keep track of this many basin's
binClass = zeros(size(Q0));   %Has a point been placed in a bin?
binEdges = -nBasinTrack*pi:2*pi:nBasinTrack*pi;
binCenters = 0.5*(binEdges(1:(end-1)) + binEdges(2:end));    

z = Z0;
t = 0;
idxTrack = binClass == 0;
for iter=1:100
     
    x = z(:,idxTrack);
    
    % Numerical integration of system (only track current state)
    nStep = 100;  dt = 2*pi/nStep;
    time = linspace(t, t+2*pi, nStep);
    for i=1:nStep
        k1 = dynSys(time(i),  x);
        k2 = dynSys(time(i)+0.5*dt,  x + 0.5*dt*k1);
        k3 = dynSys(time(i)+0.5*dt,  x + 0.5*dt*k2);
        k4 = dynSys(time(i)+dt,  x + dt*k3);
        x = x + (dt/6)*(k1+2*k2+2*k3+k4);
    end
    t = t + 2*pi;
    z(:,idxTrack) = x;
    
    % Points that have left the field of search. These could technically
    % return, but we drop them to reduce the search space.
    idxFar = x(1,:) <= binEdges(1) | x(1,:) >= binEdges(end);
    binClass(idxTrack(idxFar)) = -1;
    
    % Compute the bin of each point:
    [n,~,bin] = histcounts(x(1,:),binEdges);
    for i=1:nBasinTrack
        idxBin = bin == i;
        pts = x(:,idxBin);  %All points in this bin
        dist = (pts(1,:)+2.0463+binCenters(i)).^2 + (pts(2,:)-0.3927).^2;
        idxBasin = dist < 0.1.^2;
        binClass(idxTrack(idxBin(idxBasin))) = i;  
    end
    idxTrack = binClass == 0;
    
    
end







