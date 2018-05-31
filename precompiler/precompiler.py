import os
import re

import paxnamespace
import paxfilewriter

# Version with class/struct definition parser
#EntityComponentRegex = ".*(PAX_ENTITYCOMPONENT)\((\s*[a-zA-Z]+\s*)(,\s*[a-zA-Z]+\s*)*\)\s+(class|struct)\s+(?P<Type>[a-zA-Z]+)\s*:\s*(?P<Parents>([a-zA-Z\s]+)(\s*,\s*([a-zA-Z\s]+))*).*"
#EntityComponentRegex = "PAX_ENTITYCOMPONENT\(\s*(?P<Type>[:a-zA-Z0-9]+)\s*,\s*(?P<Parent>[:a-zA-Z0-9]+)\s*,\s*(?P<IsMultiple>[a-zA-Z]+)\s*\)"
EntityComponentBodyRegex = "(struct|class)\s(?P<Type>[:a-zA-Z0-9]+)\s:[a-zA-Z0-9\s,:]*\s{([a-zA-Z0-9\s,;\(\):=&\*])*PAX_ENTITYCOMPONENT_BODY\(\s*(?P<Parent>[:a-zA-Z0-9]+)\s*,\s*(?P<IsMultiple>[a-zA-Z]+)\s*\)"


class EntityComponent:
    def __init__(self, name, ismultiple):
        self.name = name
        self.ismultiple = ismultiple
        self.nameWithoutNamespaces = name.replace("::", "__ns__")


class GenerationData:
    def __init__(self):
        self.includes = []


def getCppTypeOf(var):
    return "std::type_index(typeid(" + var + "))"


def scanFilesForEntityComponentInheritance(generationData, dir):
    entityComponents = []
    entityComponentInheritances = []
    includes = ["core/entity/Entity.h"]

    for root, subdirs, files in os.walk(dir):
        for filename in files:
            if filename.endswith(".h"):
                file_path = os.path.join(root, filename)
                headerFile = open(file_path, "r")
                code = headerFile.read()

                if "PAX_ENTITYCOMPONENT_BODY" in code:
                    m = entityComponentRegexPattern.search(code)
                    if m is not None:
                        ecType = m.group("Type").strip()
                        ecParent = m.group("Parent").strip()
                        ecIsMultiple = m.group("IsMultiple").strip()
                        print("Inheritance found:", ecType, "inherits", ecParent)

                        # Search for namespaces
                        enamespace = paxnamespace.getNamespace(code, ecType)
                        if (enamespace.startswith("PAX")):
                            enamespace = enamespace[3:]
                            if enamespace.startswith("::"):
                                enamespace = enamespace[2:]

                        ecFullQualifiedName = ecType
                        if enamespace:
                            ecFullQualifiedName = enamespace + "::" + ecFullQualifiedName

                        ecomp = EntityComponent(ecFullQualifiedName, ecIsMultiple)
                        ecomp.namespace = enamespace
                        ecomp.fullQualifiedName = ecFullQualifiedName
                        entityComponents.append(ecomp)
                        entityComponentInheritances.append((ecFullQualifiedName, ecParent))

                        includes.append(file_path.replace(precompilationDirectory, ""))

                headerFile.close()

    generationData.entityComponents = entityComponents
    generationData.entityComponentInheritances = [(ec, parent) for ec, parent in entityComponentInheritances if ec != "EntityComponent"]
    generationData.includes.extend(includes)


def generateEventHandlers(file, ecomp):
    file.writeLine("static void " + ecomp.nameWithoutNamespaces + "Attached(Entity* e, EntityComponent *c) {")
    file.incrementIndent()
    file.writeLine("EntityComponentAddedEvent<" + ecomp.name + "> event(static_cast<" + ecomp.name + "*>(c), e);")
    file.writeLine("e->_localEventService(event);")
    file.decrementIndent()
    file.writeLine("}")
    file.writeLine("static void " + ecomp.nameWithoutNamespaces + "Detached(Entity* e, EntityComponent *c) {")
    file.incrementIndent()
    file.writeLine("EntityComponentRemovedEvent<" + ecomp.name + "> event(static_cast<" + ecomp.name + "*>(c), e);")
    file.writeLine("e->_localEventService(event);")
    file.decrementIndent()
    file.writeLine("}")


if __name__ == "__main__":
    print("PRECOMPILER Start")
    entityComponentRegexPattern = re.compile(EntityComponentBodyRegex, re.MULTILINE)
    myPath = os.path.realpath(__file__)

    precompilationDirectory = os.path.dirname(myPath) + "/../include/"
    targetFile = os.path.dirname(myPath) + "/../src/generated/EntityComponentTypeHierarchy.generated.cpp"
    genData = GenerationData()
    genData.includes.append("generated/EntityComponentTypeHierarchy.h")
    genData.includes.append("core/entity/event/EntityComponentAddedEvent.h")
    genData.includes.append("core/entity/event/EntityComponentRemovedEvent.h")

    scanFilesForEntityComponentInheritance(genData, precompilationDirectory)

    print()
    print("Generating source file", targetFile)
    print()

    outFile = paxfilewriter.FileWriter(open(targetFile, "w"))

    for include in genData.includes:
        outFile.writeLine("#include <" + include.replace("\\", "/") + ">")

    knownTypes = ["EntityComponent", "PAX::EntityComponent"]
    inheritancePairs = []
    sortedInheritancePairs = []

    #for str_entitycomponent, str_parents in genData.entityComponentInheritances:
    #    supertypes = str_parents.split(",")
    #    for supertype in supertypes:
    #        supertypeCut = supertype.replace("public", "").replace("private", "").replace("protected", "").strip()
    #        if supertypeCut in genData.entityComponents:
    #            inheritancePairs.append((str_entitycomponent, supertypeCut))
    sortedInheritancePairs = genData.entityComponentInheritances

    # sort inheritance pairs
    while len(inheritancePairs) > 0:
        for etype, eparent in inheritancePairs:
            if eparent in knownTypes:
                sortedInheritancePairs.append((etype, eparent))
                inheritancePairs.remove((etype, eparent))
                knownTypes.append(etype)

    outFile.writeLine("")
    outFile.writeLine("namespace PAX {")
    outFile.incrementIndent()
    outFile.writeLine("namespace Generated {")
    outFile.incrementIndent()

    outFile.writeLine("TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentAttached;")
    outFile.writeLine("TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentDetached;")
    outFile.writeLine("TypeMap<bool> EntityComponentTypeHierarchy::IsMultiple;")
    outFile.writeLine("")

    addEventHandlersToMapCalls = []

    # generate event handlers for attached & detached
    eventBrokerName = "EntityComponentTypeHierarchyEventBroker";
    outFile.writeLine("class " + eventBrokerName + " {")
    outFile.writeLine("public:")
    outFile.incrementIndent()
    for entityComponent in genData.entityComponents:
        generateEventHandlers(outFile, entityComponent)
        addEventHandlersToMapCalls.append("OnEntityComponentAttached.put(" + getCppTypeOf(entityComponent.name) + ", &" + eventBrokerName + "::" + entityComponent.nameWithoutNamespaces + "Attached);")
        addEventHandlersToMapCalls.append("OnEntityComponentDetached.put(" + getCppTypeOf(entityComponent.name) + ", &" + eventBrokerName + "::" + entityComponent.nameWithoutNamespaces + "Detached);")

    outFile.decrementIndent()
    outFile.writeLine("};")
    outFile.writeLine("")

    # generate type hierarchy method calls
    outFile.writeLine("void EntityComponentTypeHierarchy::initialize() {")
    outFile.incrementIndent()

    for call in addEventHandlersToMapCalls:
        outFile.writeLine(call)

    outFile.writeLine("")
    outFile.writeLine("Reflection::TypeHierarchy &h = Entity::EntityComponentTypes;")

    for etype, eparent in sortedInheritancePairs:
        outFile.writeLine("h.add(" + getCppTypeOf(etype) + ", " + getCppTypeOf(eparent) + ");")
        print("Wrote inheritance", etype, "->", eparent)

    outFile.writeLine("")
    for entityComponent in genData.entityComponents:
        outFile.writeLine("IsMultiple.put(" + getCppTypeOf(entityComponent.name) + ", " + entityComponent.name + "::IsMultiple());")

    outFile.decrementIndent()
    outFile.writeLine("}")  # void createEntityComponentTypeHierarchy()
    outFile.decrementIndent()

    outFile.writeLine("}")  # namespace Generated
    outFile.decrementIndent()
    outFile.writeLine("}")  # namespace PAX

    outFile.close()
