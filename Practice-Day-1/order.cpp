#include <iostream>
#include "create_order_generated.h"

using namespace Orders;

int main()
{
  // Creating a buffer.
  flatbuffers::FlatBufferBuilder builder(1024);

  auto account_id = 876521987;  // ramdom 9-digit ID
  auto order_id = 1923742;  // random 7-digit ID
  auto symbol = builder.CreateString("WIPRO");
  auto buy_quantity = 150;
  auto buy_price = 630.50;
  
  auto buy_order = CreateCreateOrder(builder, account_id, order_id, Exchange_NSE,
                                      symbol, OrderType_CNC, buy_quantity,
                                      buy_price, Action_BUY);

  builder.Finish(buy_order); 

  // Reading from the above created buffer.
  auto order = GetCreateOrder(builder.GetBufferPointer());

  std::cout << "Account ID: " << order->account_id() << "\n";
  std::cout << "Order ID: " << order->order_id() << "\n";
  std::cout << "Exchange: " << order->exchange() << "\n";
  std::cout << "Symbol: " << order->symbol()->str() << "\n";  
  std::cout << "Order Type: " << order->order_type() << "\n";
  std::cout << "Quantity: " << order->quantity() << "\n";
  std::cout << "Price: " << order->price() << "\n";
  std::cout << "Action: " << order->action() << "\n";

  std::cout << "\nVerifying data...\n";
  assert(account_id == order->account_id()); 
  assert(order_id == order->order_id());
  assert("WIPRO" == order->symbol()->str());
  assert(buy_quantity == order->quantity());
  assert(buy_price == order->price());
  std::cout << "Flatbuffer was successfully verified!\n";
  
  return 0;
}
