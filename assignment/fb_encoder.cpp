#include <iostream>
#include <vector>
#include "Client_generated.h"
#include <fstream>

using namespace Client;

// Write an example Client::Person.
void WritePerson(flatbuffers::FlatBufferBuilder& builder)
{
  auto pName = builder.CreateString("Ram");
  auto pAge = 21;
  auto pWeight = 76.5;

  auto Person = CreatePerson(builder, pName, pAge, pWeight, Gender_Male);
  auto Data = CreateData(builder, Client::Foo_Person, Person.Union());
  
  builder.FinishSizePrefixed(Data);
}

// Write an example Client::Group.
void WriteGroup(flatbuffers::FlatBufferBuilder& builder)
{
  auto gName = builder.CreateString("FightClub");
  auto gAge = 24.5;
  auto gWeight = 66;
  flatbuffers::Offset<flatbuffers::String> Names[] = {
                                                      builder.CreateString("Ram"),
                                                      builder.CreateString("Shayam"),
                                                      builder.CreateString("Raghuveer")
                                                     };
  auto gNameList = builder.CreateVector(Names, 3);

  auto Group = CreateGroup(builder, gName, gAge, gWeight, gNameList);
  auto Data = CreateData(builder, Client::Foo_Group, Group.Union());

  builder.FinishSizePrefixed(Data);
}

int main()
{
  flatbuffers::FlatBufferBuilder builder(1024);
  uint8_t* buf;
  int size;

  // Open the file for writing.
  std::ofstream writer("fb_bytes.bin", std::ios_base::app | std::ios::binary);

  // Create Client::Person.
  WritePerson(builder);

  // Getting ready to the write buffer to a file.
  buf = builder.GetBufferPointer();
  size = builder.GetSize();
    
  // Writing to a file.
  writer.write((char*)buf, size);  
  
  // Clearing the builder.
  builder.Clear();

  // Create Client::Group.
  WriteGroup(builder);
  
  // Getting ready to the write buffer to a file.
  buf = builder.GetBufferPointer();
  size = builder.GetSize();
  
  // Writing to a file.
  writer.write((char*)buf, size);  
  writer.close();

  return 0;
}
