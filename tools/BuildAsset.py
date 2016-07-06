import sys

RESOURCE_FOLDER = "..\\res\\"
MODEL_FOLDER = "models\\"

def Build(filename):
    extension = filename.split(".")[-1]
    result = 0

    if(extension == "dae"):
        result += BuildModel(filename)

    if(result == 0):
        print("All assets have finished building successfully.")
    else:
        print("Error occured during building. Check output for more information.")

def BuildModel(filename):
    try:
        f = open(RESOURCE_FOLDER + MODEL_FOLDER + filename, 'r');
    except:
        print("Error opening file %s" % filename);
        return 1

    print(f)

    return 0

Build(sys.argv[1]);
