function plotData(csv_file)
    data = csvread(csv_file)
    X = data(:,1);
    Y = data(:,2);
    Z = data(:,3);
    plot3(X,Y,Z, '.')
    xlabel('x coordinate (in)')
    ylabel('y coordinate (in)')
    zlabel('height (in)')
end