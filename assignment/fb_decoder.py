import flatbuffers
import Client.Data
import Client.Group
import Client.Person
import Client.Foo
import Client.Gender

# Open the binary file.
with open("fb_bytes.bin", "rb") as f:
    reader = f.read()

while (reader):
  # Extract the size of message.
  message_size = int(' '.join(str(c) for c in reader[:1]))

  # Remove the size prefix data from the buffer.
  reader = reader[4:]
  
  client = Client.Data.Data.GetRootAs(reader, 0)

  # If data is a Person.
  if client.DataType() == Client.Foo.Foo().Person:
    data = Client.Person.Person()
    data.Init(client.Data().Bytes, client.Data().Pos)
  
    if data.Gender() == 0:
      gender = "Female"
    elif data.Gender() == 1:
      gender = "Male"
  
    print("{", end = "")
    print(data.Name().decode('utf-8'), end = ", ")
    print(str(data.Age()), end = ", ")
    print(str(data.Weight()), end = ", ")
    print(gender, end = "}\n")
  
  # If data is a Group.
  elif client.DataType() == Client.Foo.Foo().Group:
    data = Client.Group.Group()
    data.Init(client.Data().Bytes, client.Data().Pos)
  
    print("{", end = "")
    print(data.GroupName().decode('utf-8'), end = ", ")
    print(str(data.AverageAge()), end = ", ")
    print(str(data.AverageWeight()), end = ", ")
    print("{", end = "")
    for i in range(data.NamesLength()):
      print(data.Names(i).decode("utf-8"), end = ",")
    print("}}")
  
  reader = reader[message_size:]
