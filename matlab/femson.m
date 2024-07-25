clc, clearvars, close all;

fileName = 'test.json';
jsonText = fileread(fileName);
data = jsondecode(jsonText);

% Nodes matrix
nodes = struct2table(data.nodes);
nodes = table2array(nodes);

% Elements
Elements_id = struct2table(data.elements);
Elements_id = table2array(Elements_id(:,1)); 

% Element matrix definition
sz = size(Elements_id); 

switch data.elements(1).type

    case 's4'
        Elements_nodes = zeros(sz(1),4);
        for i = 1:sz(1)
            Nodes = data.elements(i).nodes;
            Elements_nodes(i,:) = Nodes';
            clear Nodes
        end
        Elements = horzcat(Elements_id, Elements_nodes);
        clear i
        for i = 1:sz(1) 
            A = Elements(i,2:end);
            Vertices = nodes(A,2:end);
            x = Vertices(:,1)';
            y = Vertices(:,2)';
            z = Vertices(:,3)';
            
            fill3(x,y,z,'k','FaceAlpha',0.5)
            hold on
        end
        axis equal

    case 's8'
        Elements_nodes = zeros(sz(1),8);
        for i = 1:sz(1)
            Nodes = data.elements(i).nodes;
            Elements_nodes(i,:) = Nodes';
            clear Nodes
        end
        Elements = horzcat(Elements_id, Elements_nodes);
        % Element position 
        clear i
        for i = 1:sz(1) 
            A = Elements(i,2:end);
            A = [A(1) A(5) A(2) A(6) A(3) A(7) A(4) A(8)];
            Vertices = nodes(A,2:end);
            x = Vertices(:,1)';
            y = Vertices(:,2)';
            z = Vertices(:,3)';
            
            fill3(x,y,z,'k','FaceAlpha',0.5)
            hold on
        end
        axis equal

    case 's9'
        Elements_nodes = zeros(sz(1),9);
        for i = 1:sz(1)
            Nodes = data.elements(i).nodes;
            Elements_nodes(i,:) = Nodes';
            clear Nodes
        end
        Elements = horzcat(Elements_id, Elements_nodes);
        clear i
        for i = 1:sz(1) 
            A = Elements(i,2:end-1);
            A = [A(1) A(5) A(2) A(6) A(3) A(7) A(4) A(8)];
            Vertices = nodes(A,2:end);
            x = Vertices(:,1)';
            y = Vertices(:,2)';
            z = Vertices(:,3)';
            
            fill3(x,y,z,'k','FaceAlpha',0.5)
            hold on
        end
        axis equal

end







