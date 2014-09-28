function plotData(csv_file, max_depth)
    data = csvread(csv_file);
    
    Tilt = data(:,1) .* (pi/180);
    Pan = data(:,2) .* (pi/180);
    Z = data(:,3);
    
    for i = 1:length(Z)
        if Z(i) > 2*max_depth
            Z(i) = 0;
        end
    end
    
    [x,y,z] = sph2cart(Pan,Tilt,Z);
   
    plot3(x,y,z, '.')
    
    tri = delaunay(Pan,Tilt);
    trisurf(tri,Pan,Tilt,Z)

    xlabel('x coordinate (in)')
    ylabel('y coordinate (in)')
    zlabel('height (in)')
end