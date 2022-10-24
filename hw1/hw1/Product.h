#pragma once

#include "ProductCategory.h"
#include <iostream>

class Product
{
public:
  Product(int id, float price, std::string description,
          ProductCategory category)
      : id(id), price(price), description(description), category(category)
  {
  }

  void print(std::ostream& cout = std::cout) const;

  ProductCategory getCategory() const { return this->category; }

private:
  const int       id;
  float           price;
  std::string     description;
  ProductCategory category;
};