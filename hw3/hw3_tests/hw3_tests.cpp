#include "pch.h"
#include "CppUnitTest.h"

#include "Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace hw3tests
{
	TEST_CLASS(hw3tests)
	{
	public:

		TEST_METHOD(when_calling_get_name_the_name_is_correctly_returned)
		{
			const auto* name = "van1";
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan(name));

			Assert::IsTrue(strcmp(van->getName(), name) == 0);
			Assert::IsTrue(van->getName() != name);

			auto* actualName = van->getName();
			actualName[0] = 'f';

			Assert::IsTrue(van->getName() != name);
		}

		TEST_METHOD(when_calling_set_name_the_name_is_correctly_set)
		{
			const auto* name = "van1";
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());
			van->setName(name);

			Assert::IsTrue(strcmp(van->getName(), name) == 0);
			Assert::IsTrue(van->getName() != name);

			auto* actualName = van->getName();
			actualName[0] = 'f';

			Assert::IsTrue(van->getName() != name);
		}

		TEST_METHOD(when_calling_get_load_the_load_is_correctly_returned)
		{
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());

			Assert::IsTrue(van->getLoad() == 0);
		}

		TEST_METHOD(when_calling_get_package_the_packages_are_correctly_returned)
		{
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());

			auto* firstCall = van->getPackages();
			auto* secondCall = van->getPackages();

			Assert::IsTrue(firstCall != nullptr);
			Assert::IsTrue(firstCall != secondCall);
		}

		TEST_METHOD(when_calling_delivery_van_constructor_a_van_is_constructed)
		{
			const auto* name = "van1";
			const auto expectedMaxLoad = 10;
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan(name));

			Assert::IsTrue(strcmp(van->getName(), name) == 0);
			Assert::IsTrue(van->getName() != name);
			Assert::IsTrue(van->getLoad() == 0);
			Assert::IsTrue(van->getPackages() != nullptr);
			Assert::IsTrue(DeliveryVan::MAX_LOAD == expectedMaxLoad);

			auto* actualName = van->getName();
			actualName[0] = 'f';

			Assert::IsTrue(van->getName() != name);
		}

		TEST_METHOD(when_calling_delivery_van_default_constructor_a_van_is_constructed_with_default_values) {
			const auto* defaultName = "default";
			const auto expectedMaxLoad = 10;
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());

			Assert::IsTrue(strcmp(van->getName(), defaultName) == 0);
			Assert::IsTrue(van->getName() != defaultName);
			Assert::IsTrue(van->getLoad() == 0);
			Assert::IsTrue(van->getPackages() != nullptr);
			Assert::IsTrue(DeliveryVan::MAX_LOAD == expectedMaxLoad);

			auto* actualName = van->getName();
			actualName[0] = 'f';

			Assert::IsTrue(van->getName() != defaultName);
		}

		TEST_METHOD(when_calling_add_package_a_package_is_added) {
			const auto packageWeight = 1;
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());
			van->addPackage(packageWeight);

			auto* actualPackages = van->getPackages();
			Assert::IsTrue(actualPackages != nullptr);
			Assert::IsTrue(actualPackages[0] == packageWeight);
		}

		TEST_METHOD(when_calling_add_package_and_max_load_is_reached_an_exception_is_thrown) {
			const auto packageWeight = 1;
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());

			for (auto i = 0; i < DeliveryVan::MAX_LOAD; ++i) {
				van->addPackage(packageWeight);
			}

			try {
				van->addPackage(packageWeight);
				Assert::IsTrue(false);
			}
			catch (const std::exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(when_calling_delivery_van_copy_constructor_a_van_is_copied) {
			const auto* name = "van1";
			const auto expectedMaxLoad = 10;
			const auto packageWeight = 1;
			DeliveryVan van(name);
			van.addPackage(packageWeight);

			std::unique_ptr<BaseDeliveryVan> copy(new DeliveryVan(van));

			Assert::IsTrue(strcmp(copy->getName(), van.getName()) == 0);
			Assert::IsTrue(copy->getName() != van.getName());
			Assert::IsTrue(copy->getLoad() == van.getLoad());

			auto* actualPackages = copy->getPackages();
			auto* expectedPackages = van.getPackages();
			auto noPackages = van.getLoad();

			Assert::IsTrue(actualPackages != nullptr);
			Assert::IsTrue(actualPackages[0] == packageWeight);

			actualPackages[0] *= 2;

			actualPackages = copy->getPackages();
			Assert::IsTrue(actualPackages != nullptr);
			Assert::IsTrue(actualPackages[0] == packageWeight);
		}

		TEST_METHOD(when_calling_delivery_van_copy_assignment_a_van_is_copied) {
			const auto* name = "van1";
			const auto expectedMaxLoad = 10;
			const auto packageWeight = 1;
			DeliveryVan van(name);
			van.addPackage(packageWeight);

			DeliveryVan copy("");
			copy = van;

			Assert::IsTrue(strcmp(copy.getName(), van.getName()) == 0);
			Assert::IsTrue(copy.getName() != van.getName());
			Assert::IsTrue(copy.getLoad() == van.getLoad());

			auto* actualPackages = copy.getPackages();
			auto* expectedPackages = van.getPackages();
			auto noPackages = van.getLoad();

			Assert::IsTrue(actualPackages != nullptr);
			Assert::IsTrue(actualPackages[0] == packageWeight);

			actualPackages[0] *= 2;

			actualPackages = copy.getPackages();
			Assert::IsTrue(actualPackages != nullptr);
			Assert::IsTrue(actualPackages[0] == packageWeight);
		}

		TEST_METHOD(when_calling_delivery_van_pre_increment_a_package_with_weight_1_is_added) {
			const auto packageWeight = 1;
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());
			++(*van.get());

			Assert::IsTrue(van->getLoad() == 1);
			Assert::IsTrue(van->getPackages()[0] == packageWeight);
		}

		TEST_METHOD(when_comparing_delivery_vans_the_expected_result_is_returned) {
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());
			++(*van.get());

			std::unique_ptr<BaseDeliveryVan> van2(new DeliveryVan());
			++(*van2.get());

			Assert::IsTrue((*van.get()) == (*van2.get()));
		}

		TEST_METHOD(when_comparing_delivery_vans_the_expected_result_is_returned_2) {
			std::unique_ptr<BaseDeliveryVan> van(new DeliveryVan());
			++(*van.get());

			std::unique_ptr<BaseDeliveryVan> van2(new DeliveryVan());

			Assert::IsTrue((*van.get()) != (*van2.get()));
		}
	};
}
