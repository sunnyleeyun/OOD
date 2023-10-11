// To monitor the process of how to put the package into a right locker. and one locker for one package. your package and locker have different size, you need to make sure the locker size > package.
// sounds like similar with Parking lot right? Let's desgin a locker!
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Size
{
    SMALL,
    MEDIUM,
    LARGE
};

class Package
{
    // size, id
private:
    string id;
    Size size;

public:
    Package(string id, Size size) : id(id), size(size) {}

    string getId()
    {
        return id;
    }

    Size getSize()
    {
        return size;
    }
};

class Locker
{
    // package id = empty str or a package id
    // isEmpty method return true or false
    // fillPackage(packageId)
    // retrievePackage(packageId) clear the package id
private:
    string id;
    Size size;
    bool empty;
    string verificationCode;

    string generateVerificationCode(string packageId)
    {
        return "123456";
    }

public:
    Locker(string id, Size size) : id(id), size(size), empty(true), verificationCode("") {}

    string getId()
    {
        return id;
    }

    Size getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return empty;
    }

    // return true if success else false
    string putAndgetVerificationCode(string packageId)
    {
        // generate a verificationCode and store there
        verificationCode = generateVerificationCode(packageId);
        return verificationCode;
    }
    // return true if success else false
    bool enableRetrieve(string code)
    {
        return code == verificationCode;
    }
};

class LockerSystem
{
    // lockers
    // geolocation
    // isAdmin
    //
    // construtor empty locker or lockers pre-gen and pass in, isAdmin
    //
    //
private:
    double latitute;
    double longitude;
    vector<Locker> lockers;
    bool isAdmin;

    Locker findMatchLocker(Package package)
    {
        // return locker that matches iterating from the smallest
        for (auto &locker : lockers)
        {
            if (locker.getSize() >= package.getSize())
            {
                return locker;
            }
        }
        throw invalid_argument("Locker Not Found");
    }

    Locker findLocker(string lockerId, Package package)
    {
        // return locker that matches the same locker id
        for (auto &locker : lockers)
        {
            if (locker.getId() == lockerId)
            {
                return locker;
            }
        }
        throw invalid_argument("Locker Not Found");
    }

public:
    LockerSystem(double latitute, double longitude, bool isAdmin) : latitute(latitute), longitude(longitude), isAdmin(isAdmin) {}

    bool addLocker()
    {
        // add and sort
    }

    bool removeLocker(string lockerId)
    {
        // remove and sort
    }

    // return verification code or throw an error, such as no more lockers
    string store(Package package)
    {
        Locker locker = findMatchLocker(package);
        string packageId = package.getId();
        string verificationId = locker.putAndgetVerificationCode(packageId);
        return verificationId;
    }

    bool retrieve(string lockerId, string verificationId)
    {
        try
        {
            Locker locker = findLocker(lockerId);
            return locker.enableRetrieve(verificationId);
        }
        catch (invalid_argument &e)
        {
            throw e;
        }
    }
};

// Questions:
// 1. Do I have to worry about access control?
// 2. Is it ok to allocate SMALL, MEDIUM, LARGE in advance
// 3. Can we add more locker or remove locker?
// 4. Do I have to take it out from the locker?
// 5. How am I gonna retrieve it? 6 unit verification code.

// 1. LockerSystem <|- Lockers : Locker[]
// 2. LockerSystem <Package> -> method: store(package) and retrive(package id)
// 3. LockerSystem <Lockers> -> method: addLocker(size) and deleteLocker(locker id)

// Use case:
// User can store a package
// User can retrieve the package from the lockers
// Admin can add locker
// Admin can remove a locker
