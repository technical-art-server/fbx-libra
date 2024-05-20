import flatbuffers

from FbxLibra.CounterWeight import Hierarchy, Node, Transform

buf = open("sample.hcw", "rb").read()
buf = bytearray(buf)
hierarchy = Hierarchy.Hierarchy.GetRootAsHierarchy(buf, 0)
    
print()

for i in range(hierarchy.NodesLength()):
    print(hierarchy.Nodes(i).Name().decode("utf-8"))
    transform: Transform.Transform = hierarchy.Nodes(i).Transform()
    print(transform.Position().X(), transform.Position().Y(), transform.Position().Z())
    print(transform.Rotation())
    print(transform.Scale())
