#include "CSVHandler.h"

CSVHandler::CSVHandler(Store &store)
{
    unordered_map<string, unordered_map<string, Item>> &items = store.getItems();
    
}

CSVHandler::~CSVHandler()
{
    //dtor
}
