# CONSTANTS
header = """
<scene>
<instance name="box" path="models/box"/>

<transform name="maze">
    <set>
        <scale>5 5 5</scale>
        <translate>0 0 0</translate>
    </set>

    <group>
"""

footer = """
    </group>

</transform>

</scene>
"""

def getCellString(x, z, l, t, r, b):
    top = right = bottom = left = ""

    if l:
        left = """<group from="models/wall-left.xml"></group>"""
    if t:
        top = """<group from="models/wall-top.xml"></group>"""
    if r:
        right = """<group from="models/wall-right.xml"></group>"""
    if b:
        bottom = """<group from="models/wall-bottom.xml"></group>"""

    return """
        <transform>
            <set>
                <translate>{0:.2f} 0 {1:.2f}</translate>
            </set>
            <group>
                <group from="models/floor.xml"></group>
                {2}
                {3}
                {4}
                {5}
            </group>
        </transform>
""".format(x, z, top, right, bottom, left)

def str_to_dec_to_bin(n):
    return bin(int(n))[2:].rjust(4, "0")

def main():
    mazeResultFile = open("Assignment3/Assignment3/models/maze.xml", "w")
    mazeInputFile = open("C:\Users\matheus\git\IT356\Maze1\Maze1\maze-edited.txt", "r")

    mazeResultFile.write(header)

    # Read number os rows and columns
    rows = int(mazeInputFile.readline())
    columns = int(mazeInputFile.readline())

    # Skip start and end
    mazeInputFile.readline()

    # Calculate start x,z index
    x = 0.45 * (columns - 1) * -1
    z = 0.45 * (rows - 1) * -1

    for r in range(rows, 0, -1):

        walls = [str_to_dec_to_bin(e) for e in mazeInputFile.readline().split(" ") if e != "\n"]

        for c in range(columns, 0, -1):
            cellWalls = walls[columns - c]

            left = int(cellWalls[0])
            top = int(cellWalls[1])
            right = int(cellWalls[2]) and (c - 1 == 0) # only if it is right border
            bottom = int(cellWalls[3]) and (r - 1 == 0) # only if it is bottom border

            mazeResultFile.write(getCellString(x, z, left, top, right, bottom))
            x += 0.9

        z += 0.9
        x = 0.45 * (columns - 1) * -1

    mazeResultFile.write(footer)

    mazeInputFile.close()
    mazeResultFile.close()

main()
