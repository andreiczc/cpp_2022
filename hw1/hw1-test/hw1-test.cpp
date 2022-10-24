#include "pch.h"
#include "CppUnitTest.h"

#define private public

#include "ProductCategory.h"
#include "Product.h"
#include "ShoppingCart.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace hw1test
{
	TEST_CLASS(hw1test)
	{
	public:
		
		TEST_METHOD(when_calling_product_constructor_an_object_is_created) {
				const auto id = 1;
				const auto price = 21.5f;
				const std::string description = "test";
				const ProductCategory category = ProductCategory::GAMING;

				Product product(id, price, description, category);

				Assert::AreEqual(id, product.id);
				Assert::AreEqual(price, product.price);
				Assert::AreEqual(description, product.description);
				Assert::IsTrue(category == product.category);
		}

		TEST_METHOD(when_calling_product_print_the_info_is_displayed) {
				Product product(1, 21.5, "test", ProductCategory::GAMING);
				std::stringstream output;

				product.print(output);

				Assert::AreEqual("Product 1 is a test and costs 21.5\n", output.str().c_str());
		}

		TEST_METHOD(when_calling_shopping_cart_constructor_an_object_is_created) {
				const std::string customerName = "customer1";

				ShoppingCart cart(customerName);
				
				Assert::AreEqual(customerName, cart.customerName);
				Assert::IsNotNull(cart.products);
		}

		TEST_METHOD(when_adding_a_product_to_shopping_cart_the_cart_is_updated) {
				const std::string customerName = "customer1";
				const auto id = 1;
				const auto price = 21.5f;
				const std::string description = "test";
				const ProductCategory category = ProductCategory::GAMING;

				Product product(id, price, description, category);

				ShoppingCart cart(customerName);
				cart.addProduct(&product);

				Assert::AreEqual(id, cart.products[0]->id);
				Assert::AreEqual(price, cart.products[0]->price);
				Assert::AreEqual(description, cart.products[0]->description);
				Assert::IsTrue(category == cart.products[0]->category);
		}

		TEST_METHOD(when_adding_too_many_products_an_error_is_occuring) {
				const std::string customerName = "customer1";
				const auto id = 1;
				const auto price = 21.5f;
				const std::string description = "test";
				const ProductCategory category = ProductCategory::GAMING;

				Product product(id, price, description, category);

				ShoppingCart cart(customerName);
				for (auto i = 0; i < 100; ++i) {
						cart.addProduct(&product);
				}

				Assert::ExpectException<std::runtime_error>([&cart, &product] { cart.addProduct(&product); });
		}

		TEST_METHOD(when_displaying_products_by_category_the_correct_products_are_displayed) {
				const std::string customerName = "customer1";
				const auto id = 1;
				const auto price = 21.5f;
				const std::string description = "test";
				const ProductCategory category = ProductCategory::GAMING;

				Product product1(1, 21.5f, "gaming", ProductCategory::GAMING);
				Product product2(2, 23.5f, "sports", ProductCategory::SPORTS);
				ShoppingCart cart(customerName);

				cart.addProduct(&product1);
				cart.addProduct(&product2);

				std::stringstream output;
				cart.printByCategory(ProductCategory::SPORTS, output);

				Assert::AreEqual("Product 2 is a sports and costs 23.5\n", output.str().c_str());
		}
	};
}
