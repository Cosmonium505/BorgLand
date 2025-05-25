
outputFileName = "blocks.props"


inputSchema = open("schema.txt", "r")
inputSchemaLines = inputSchema.readlines()
inputSchema.close()

schemaParsed = []

blockProps = {
    "B": 0b00000000, # Base (basically a block)
    "S": 0b00000001, # Solid
    "I": 0b00000010, # Invisible
    "P": 0b00000100, # Player Spawn
    "K": 0b00001000, # Killbrick
    "T": 0b00010000, # Sticky
    "J": 0b00100000, # Jump pad
    "X": 0b01000000, # Breakable
    "L": 0b10000000  # Level Swap

} # Reminder: Add Gravity Field and a Reverse Gravity Field. Also add the property to the gravity field.
# Add "C" for climbable when snow adds the bit expansion (to 32 bits.)

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
    