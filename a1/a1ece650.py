#!/usr/bin/env python3
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




def gg(streets):
    index = 0
    main_verts = set()
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
                        j = j + 1
            i = i +1
    print("Main verts:",main_verts)


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
        line = sys.stdin.readline()
        if line == "":
            break

        if getGG(line, streets):
            continue


        if "+" in line:
            print("Error: + operator not allowed")
            break




        if re.findall('add+\s"[^"]*"\s\(',line):
            cords = re.findall('\s\([^)]*\)',line)
            street_name = re.findall('"(.*?)"',line)
            print("streets",street_name)



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

            streets[street_name] = []
            for cord in cords:
                numbers = re.findall('-[0-9]+|[0-9]+', cord)
                print(cord)
                if len(numbers) != 2:
                    print("Invalid input : Wrong co-ordinates")
                    continue

                streets[street_name].append((int(numbers[0]),int(numbers[1])))
        else:
            print("Error: No brackets")







        print("read a line:", streets)

    print("Finished reading input")
    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == "__main__":
    main()
