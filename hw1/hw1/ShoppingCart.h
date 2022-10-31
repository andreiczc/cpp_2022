#pragma once

#include "Product.h"
#include "ProductCategory.h"
#include <iostream>

class ShoppingCart
{
public:
  ShoppingCart(std::string customerName);

  void addProduct(const Product* product);

  void printByCategory(ProductCategory category,
                       std::ostream&   cout = std::cout);

private:
  std::string     customerName;
  const Product** products;
  int             noProducts;
};