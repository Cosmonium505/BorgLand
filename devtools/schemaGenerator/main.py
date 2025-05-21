import binascii
import os

outputFileName = "blocks.props"

outputFile = open(outputFileName, "wb")

inputSchema = open("schema.txt", "r")
inputSchemaLines = inputSchema.readlines()
inputSchema.close()

schemaParsed = {}

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
    name = lineArgs[2]
    
    lineDict = {"id": id, "props": props, "name": name}

outputFile.write(len(schemaParsed).to_bytes(4, byteorder='little'))
for line in schemaParsed:
    lineDict = schemaParsed[line]
    
    parsedProps = blockProps["B"]
    for prop in lineDict["props"]:
        if prop in blockProps:
            parsedProps |= blockProps[prop]
    
    outputFile.write(lineDict["id"].to_bytes(4, byteorder='little'))
    outputFile.write(parsedProps.to_bytes(1, byteorder='little'))
    outputFile.write(b'\x00')
    outputFile.write(lineDict["name"].encode('utf-8'))
    outputFile.write(b'\x00')
    