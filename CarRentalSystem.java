
/**
 * 1. Requirement
 * 2. Core Object
 * 3. Properties
 * 4. Methods (data flow)
 * 5. Core Methods Implementation
 * 6. Optimization
 */

/**
 * Requirement
 * 1. User shall reserve a car
 * 2. User shall pickup/return a car
 */

import java.util.ArrayList;
import java.util.List;

class Car {
    private int carID;
    private String model;
    private String brand;
    private int year;
    private String color;
    private String status;
    private RentalTransaction rentalDetails;

    // Constructors, getters, setters

    public void rent(Customer customer, RentalTransaction rentalTransaction) {
        if (this.status.equals("available")) {
            this.status = "rented";
            this.rentalDetails = rentalTransaction;
            customer.addRental(this);
            System.out.println("Car rented successfully.");
        } else {
            System.out.println("Car is not available for rent.");
        }
    }

    public void returnCar() {
        if (this.status.equals("rented")) {
            this.status = "available";
            this.rentalDetails.complete();
            this.rentalDetails = null;
            System.out.println("Car returned successfully.");
        } else {
            System.out.println("Car is not currently rented.");
        }
    }
}

class Customer {
    private int customerID;
    private String name;
    private String contactInfo;
    private List<RentalTransaction> rentalHistory;

    // Constructors, getters, setters

    public void addRental(RentalTransaction rentalTransaction) {
        rentalHistory.add(rentalTransaction);
    }
}

class RentalTransaction {
    private int transactionID;
    private Customer customer;
    private Car rentedCar;
    private String rentalStartDate;
    private String rentalEndDate;
    private double rentalCost;

    // Constructors, getters, setters

    public void complete() {
        // Calculate rental cost and update transaction details
    }
}

class RentalSystem {
    private List<Car> carInventory;
    private List<Customer> customers;

    // Constructors, getters, setters

    public List<Car> getAvailableCars() {
        List<Car> availableCars = new ArrayList<>();
        for (Car car : carInventory) {
            if (car.getStatus().equals("available")) {
                availableCars.add(car);
            }
        }
        return availableCars;
    }

    public void returnCar(Car car) {
        car.returnCar();
    }

    public void rentCar(Customer customer, Car car, RentalTransaction rentalTransaction) {
        car.rent(customer, rentalTransaction);
    }
}

class Client {
    public static void main(String[] args) {
        // Sample usage of the car rental system
        RentalSystem rentalSystem = new RentalSystem();
        Car car1 = new Car(/* car details */);
        Car car2 = new Car(/* car details */);

        Customer customer = new Customer(/* customer details */);

        rentalSystem.getAvailableCars().forEach(System.out::println);

        RentalTransaction rentalTransaction = new RentalTransaction(/* transaction details */);
        rentalSystem.rentCar(customer, car1, rentalTransaction);

        rentalSystem.returnCar(car1);
    }
}
