#!/usr/bin/env python3
import math
import sys
import re
# YOUR CODE GOES HERE
def intersection(l1, l2):
    x1, y1 = l1[0][0], l1[0][1]
    x2, y2 = l1[1][0], l1[1][1]
    x3, y3 = l2[0][0], l2[0][1]
    x4, y4 = l2[1][0], l2[1][1]

    xnum = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
    xden = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))


    ynum = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)
    yden = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if xden == 0 or yden == 0:
        return (None,None)
    xcoor = xnum / xden
    ycoor = ynum / yden
    if max(x1, x2) >= xcoor >= min(x1, x2) and \
            max(y1, y2) >= ycoor >= min(y1, y2) and \
            max(x3, x4) >= xcoor >= min(x3, x4) and \
            max(y3, y4) >= ycoor >= min(y3, y4):
        return xcoor, ycoor
    return (None, None)


def get_intersections(l1,l2,inters,main_edges):
    if l1 in main_edges:
        main_edges[l1].add(inters)
    else:
        main_edges[l1] = {inters}
    if l2 in main_edges:
        main_edges[l2].add(inters)
    else:
        main_edges[l2] = {inters}
    return main_edges

def samepts(point1,point2):
    if point1[0]==point2[0] and point1[1] == point2[1]:
        return True
    return False

def final_edges(main_edges):
    final_edges = set()
    for edges in main_edges:
        points = main_edges[edges]
        points = list(points)
        edges = list(edges)
        if len(points) == 1:
            if not samepts(list(edges[0]),list(points[0])):
                final_edges.add((edges[0],points[0]))
            if not samepts(list(edges[1]), list(points[0])):
                final_edges.add((points[0],edges[1]))
        else:
            inters = []
            for point in points:
                point_meta = {}
                point_meta['d'] = math.dist(point,points[0])
                point_meta['c'] = point
                inters.append(point_meta)
            sorted_inters = sorted(inters, key=lambda d: d['d'])
            for i in range(0,len(sorted_inters)):
                if i == 0:
                    if not samepts(list(edges[0]), list(sorted_inters[i]['c'])):
                        final_edges.add((edges[0],sorted_inters[i]['c']))
                if i != (len(sorted_inters)-1):
                    if not samepts(list(edges[0]), list(sorted_inters[i+1]['c'])):
                        final_edges.add((sorted_inters[i]['c'],sorted_inters[i+1]['c']))
                if i == len(sorted_inters)-1:
                    if not samepts(list(edges[1]), list(sorted_inters[i]['c'])):
                        final_edges.add((sorted_inters[i]['c'],edges[1]))
    return final_edges

def print_results(edges,vertices):
    print("V {}".format(len(vertices)))
    sys.stdout.flush()

    edge_print = []

    for e in range(len(edges)):
        for i in range(len(vertices)):
            if list(edges)[e][0] == list(vertices)[i]:
                start_index = i 
                for d, x in enumerate(vertices):
                    if list(edges)[e][1] == x:
                        end_index = d
                        edge_print.append((start_index, end_index))

    print('E {', end = '')
    
    for i, e in enumerate(edge_print):
        if i != (len(edge_print) - 1):
            print("<{},{}>,".format(e[0], e[1]),end  = "")
        else:
            print("<{0},{1}>".format(e[0], e[1]),end = "")
            print("}")
    sys.stdout.flush()

def gg(streets):
    index = 0
    main_verts = set()
    main_edges = {}
    for street_name in streets:
        i = 0
        vert = streets[street_name]
        while i < len(vert)-1:
            x1 = vert[i][0]
            y1 = vert[i][1]
            x2 = vert[i+1][0]
            y2 = vert[i+1][1]
            for street in streets:
                j = 0
                if street != street_name:
                    vert2 = streets[street]
                    while j < len(vert2)-1:
                        x3 = vert2[j][0]
                        y3 = vert2[j][1]
                        x4 = vert2[j + 1][0]
                        y4 = vert2[j + 1][1]
                        intx, inty = intersection([[x1, y1], [x2, y2]], [[x3, y3], [x4, y4]])
                        if intx and inty:
                            main_verts.add((x1, y1))
                            main_verts.add((x2, y2))
                            main_verts.add((x3, y3))
                            main_verts.add((x4, y4))
                            main_verts.add((intx, inty))
                            main_edges = get_intersections((vert[i],vert[i + 1]),(vert2[j],vert2[j + 1]),(intx,inty),main_edges)
                        j = j + 1
            i = i +1
    print_results(final_edges(main_edges), main_verts)

def getGG(line, streets):
    gg_cmd = re.compile('^gg$')
    if gg_cmd.match(line):
        gg(streets)
        return True
    return False

def main():
    # YOUR MAIN CODE GOES HERE

    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment
    streets = {}
    while True:
        flag = True
        line = sys.stdin.readline()
        if line == "":
            break
        if getGG(line, streets):
            streets.clear()
            continue
        if "+" in line:
            print("Error: + operator not allowed")
            continue
        rm = re.compile('rm "[^"]*"')
        if rm.match(line):
            street_name = re.findall('\"(.*?)\"', line)
            cords = re.findall('\s\([^)]*\)', line)
            if len(cords) > 0:
                print("Error: Can't have 2 args")
            if len(street_name) != 1:
                print("Error: Multiple street entries")
            if street_name[0] not in streets:
                print("Error: Street doesn't exists")
            if street_name[0] == " ":
                print("Error: No street name")
            if street_name[0] in streets:
                streets.pop(street_name[0], None)
            flag = False

        if re.findall('mod+\s"[^"]*"\s\(', line):
            cords = re.findall('\s\([^)]*\)', line)
            street_name = re.findall('\"(.*?)\"', line)
            if len(street_name) != 1:
                print("Error: Multiple street entries")
                continue
            if street_name[0] not in streets:
                print("Error: Street doesn't exists")
                continue
            if line.count('(') != line.count(')'):
                print("Error: Invalid brackets")
                continue

            if len(cords) != line.count("("):
                print("Error: No spaces between brackets")
                continue

            if street_name[0] == " ":
                print("Error: No street name")
                continue

            if len(cords) == 1:
                print("Error: atleast 2 coords are needed")
                continue

            if bool(re.search(r'\d', street_name[0])):
                print("Error: numbers not permissible in street name")
                continue

            if (bool(re.match('^[a-zA-Z0-9]*$', street_name[0])) == True):
                print("Error: punctuations not permissible in street name")
                continue

            street_backup = streets[street_name[0]]
            streets[street_name[0]] = []
            for cord in cords:
                numbers = re.findall('-[0-9]+|[0-9]+', cord)
                if (' ' in cord) == True:
                    if street_name[0] in streets:
                        streets[street_name[0]] = street_backup
                    print("Invalid input : Wrong co-ordinates")
                    break
                if len(numbers) != 2:
                    streets[street_name[0]] = street_backup
                    print("Invalid input : Wrong co-ordinates")
                    break
                streets[street_name[0]].append((int(numbers[0]),int(numbers[1])))
            flag = False
        if re.findall('add+\s"[^"]*"\s\(',line):
            cords = re.findall('\s\([^)]*\)',line)
            street_name = re.findall('\"(.*?)\"',line)

            if len(street_name) != 1:
                print("Error: Multiple street entries")
                continue
            street_name = street_name[0]
            if street_name in streets:
                print("Error: Street exists")
                continue

            if line.count('(') != line.count(')'):
                print("Error: Invalid brackets")
                continue

            if len(cords) != line.count("("):
                print("Error: No spaces between brackets")
                continue
            if street_name == " ":
                print("Error: No street name")
                continue
            if bool(re.match(r'\d', street_name[0])) == True:
                print("Error: numbers not permissible in street name")
                continue
            punctuations = re.findall(r'[^\w]', street_name[0])
            if (bool(re.match(r'[^\w]', street_name[0])) == True):
                print("Error: punctuations not permissible in street name")
                continue

            if len(cords) == 1:
                print("Error: atleast 2 coords are needed")
                continue

            streets[street_name] = []
            for cord in cords:
                numbers = re.findall('-[0-9]+|[0-9]+', cord)
                if (' ' in cord.strip()) == True:
                    if street_name in streets:
                        streets.pop(street_name, None)
                    print("Invalid input : Wrong co-ordinates")
                    break
                if len(numbers) != 2:
                    print("Invalid input : Wrong co-ordinates")
                    continue

                streets[street_name].append((int(numbers[0]),int(numbers[1]))) 
            flag = False
        if flag:
            print('Error: invalid input')

    print("Finished reading input")
    sys.exit(0)


if __name__ == "__main__":
    main()
