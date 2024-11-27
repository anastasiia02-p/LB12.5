#include "pch.h"
#include "CppUnitTest.h"
#include "../LB12.4/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFile = "test_flights_delete.bin";
            Flight flights[] = {
                {"Kyiv", 1001, 3, "Boeing 737", 150, 120.5},
                {"Lviv", 1002, 2, "Airbus A320", 180, 90.0}
            };

            // Write initial data
            writeToFile(testFile, flights, 2);

            // Delete one flight
            deleteFromFile(testFile, 1001);

            // Read and assert
            Flight remainingFlights[MAX_FLIGHTS];
            int count = 0;
            readFromFile(testFile, remainingFlights, count);

            Assert::AreEqual(1, count);
            Assert::AreEqual(0, strcmp(remainingFlights[0].direction, "Lviv"));
		}
	};
}
