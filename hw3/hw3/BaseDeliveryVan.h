#pragma once

class BaseDeliveryVan {
public:
	BaseDeliveryVan(const char* name);

	BaseDeliveryVan();

	BaseDeliveryVan(const BaseDeliveryVan& otherVan);

	virtual ~BaseDeliveryVan() noexcept;

	virtual BaseDeliveryVan& operator=(const BaseDeliveryVan& otherVan);

	virtual BaseDeliveryVan& operator++();

	virtual bool operator==(BaseDeliveryVan& otherVan);

	virtual bool operator!=(BaseDeliveryVan& otherVan);

	virtual char* getName();

	virtual void setName(const char* name);

	virtual void addPackage(int weight);

	virtual int getTotalLoad();

	virtual int getLoad();

	virtual int* getPackages();

	static constexpr int MAX_LOAD = 5;

private:
	char* name;
	int* packages;
	int load;
};