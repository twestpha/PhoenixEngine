import sys
import struct

RESOURCE_FOLDER = "..\\res\\"
MODEL_FOLDER = "models\\"

OUTPUT_FOLDER = "..\\data\\"
DATA_EXTENSION = ".phx"

######################################################################################################
# Helper Functions
######################################################################################################

def getXMLValue(line): # Assumes ONE value per line
    return line.split(">")[1].split("<")[0]

######################################################################################################
# Generic entry point
######################################################################################################

def Build(filelist):
    for filename in filelist:
        extension = filename.split(".")[-1]
        result = 0

        if(extension == "dae"):
            result += BuildModel(filename)
        else:
            print("Uknown asset type %s" % extension)
            result += 1

    if(result == 0):
        print("All assets have finished building successfully.")
    else:
        print("Error occured during building. Check output for more information.")

######################################################################################################
# Building model (dae) assets
######################################################################################################

def BuildModel(filename):
    try:
        inputFile = open(RESOURCE_FOLDER + MODEL_FOLDER + filename, 'r')
    except:
        print("Error opening model file %s" % filename)
        return 1

    up_axis = 'Y'

    vertices_read = False
    num_verts = 0
    verts_x = []
    verts_y = []
    verts_z = []

    normals_read = False
    num_norms = 0
    norms_x = []
    norms_y = []
    norms_z = []

    uvs_read = False
    num_uvs = 0
    verts_u = []
    verts_v = []

    polylist_read = False
    polylist = []

    # Reading
    for line in inputFile:
        if("up_axis" in line):
            up_axis = getXMLValue(line)[0]

        if("positions-array" in line and not vertices_read): # Vertex positions
            vertices_read = True
            line = getXMLValue(line).split(" ")

            if(len(line) % 3 != 0):
                print("Error reading file %s. Wrong number of mesh vertices." % filename)
                return 1

            count = 0
            while(count < len(line)):
                verts_x.append(line[count + 0])
                verts_y.append(line[count + 1])
                verts_z.append(line[count + 2])

                count += 3

            num_verts = len(line)/3

        if("normals-array" in line and not normals_read): # Normal positions
            normals_read = True
            line = getXMLValue(line).split(" ")

            if(len(line) % 3 != 0):
                print("Error reading file %s. Wrong number of normal vectors." % filename)
                return 1

            count = 0
            while(count < len(line)):
                norms_x.append(line[count + 0])
                norms_y.append(line[count + 1])
                norms_z.append(line[count + 2])

                count += 3

            num_norms = len(line)/3

        if("map" in line and "array" in line and not uvs_read): # UV positions
            uvs_read = True
            line = getXMLValue(line).split(" ")

            if(len(line) % 2 != 0):
                print("Error reading file %s. Wrong number of UV vertices." % filename)
                return 1

            count = 0
            while(count < len(line)):
                verts_u.append(line[count + 0])
                verts_v.append(line[count + 1])

                count += 2

            num_verts = len(line)/2

        if("<p>" in line and not polylist_read): # Polylist of all the connections
            polylist_read = True
            line = getXMLValue(line).split(" ")

            if(len(line) % 3 != 0):
                print("Error reading file %s. Wrong number of polylist indices." % filename)
                return 1

            for number in line:
                polylist.append(int(number))

    inputFile.close()

    # Writing
    try:
        outputFile = open(OUTPUT_FOLDER + filename.split(".")[0] + DATA_EXTENSION, "wb")
    except:
        print("Error writing file %s, unable to open." % (filename.split(".")[0] + DATA_EXTENSION))
        return 1

    count = 0
    output = b""
    while(count < len(polylist)):
        vert_index = polylist[count + 0]
        norm_index = polylist[count + 1]
        uv_index = polylist[count + 2]

        x = 0.0
        y = 0.0
        z = 0.0

        nx = 0.0
        ny = 0.0
        nz = 0.0

        u = 0.0
        v = 0.0

        if(vertices_read):
            x = verts_x[vert_index]
            # SWAP Z AND Y UP!!!!!!
            y = verts_z[vert_index]
            z = verts_y[vert_index]

        if(normals_read):
            nx = norms_x[norm_index]
            # SWAP Z AND Y UP!!!!!!!
            ny = norms_z[norm_index]
            nz = norms_y[norm_index]

        if(uvs_read):
            u = verts_u[uv_index]
            v = verts_v[uv_index]

        # print(x, y, z, nx, ny, nz, u, v)
        vertlist = [float(x), float(y), float(z), float(nx), float(ny), float(nz), float(u), float(v)]
        s = struct.pack('=%sf' % len(vertlist), *vertlist)
        output += s

        count += 3

    outputFile.write(output)
    outputFile.close()

    print("Built %s --> %s" % (filename, filename.split(".")[0] + DATA_EXTENSION))

    return 0

######################################################################################################
# Main
######################################################################################################

try:
    Build(sys.argv[1:]);
except:
    print("Usage:\n\tBuildAsset.py [Asset(s) to build]\n\tExample: BuildAsset.py cube.dae")
