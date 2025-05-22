
outputFileName = "blocks.props"


inputSchema = open("schema.txt", "r")
inputSchemaLines = inputSchema.readlines()
inputSchema.close()

schemaParsed = []

blockProps = {
    "B": 0b00000000,
    "S": 0b00000001,
    "I": 0b00000010,
    "P": 0b00000100
}

for line in inputSchemaLines:
    lineArgs = line.split(",")
    id = int(lineArgs[0])
    props = lineArgs[1]
    name = lineArgs[2].strip()
    
    lineDict = {"id": id, "props": props, "name": name}
    schemaParsed.append(lineDict)

outputFile = open(outputFileName, "wb")
outputFile.write(len(schemaParsed).to_bytes(4, byteorder='little'))
for line in schemaParsed:
    lineTab = line
    
    parsedProps = blockProps["B"]
    for prop in lineTab["props"]:
        if prop in blockProps:
            parsedProps |= blockProps[prop]

    outputFile.write(lineTab["id"].to_bytes(4, byteorder='little'))
    outputFile.write(parsedProps.to_bytes(1, byteorder='little'))
    outputFile.write(len(lineTab["name"]).to_bytes(4, byteorder='little'))
    outputFile.write(lineTab["name"].encode('utf-8'))
    