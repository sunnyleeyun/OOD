//
//  OOD.swift
//  FlightSystem
//
//  Created by 李昀 on 2023/11/22.
//

import Foundation

protocol User {
    var name: String { get }
    var uuid: String { get }
}

class Customer: User {
    var name: String
    var uuid: String

    init(name: String, uuid: String) {
        self.name = name
        self.uuid = uuid
    }
}

class Flight {
    private var seatsDict: [String: FlightSeat] = [:]
    private var seats: [FlightSeat] // hashmap with ds of id: FlightSeat
    private let bookQueue = DispatchQueue(label: "booking")
    
    init(seats: [FlightSeat]) {
        for seat in seats {
            seatsDict[seat.seatId] = seat
        }
        self.seats = seats
    }
    
    func getAvailableSeats(seatSize: SeatSize) -> [FlightSeat] {
        return seats.filter { seat in
            !seat.isOccupy && seat.seatSize == seatSize
        }
    }
    
    func bookSeat(seatId: String, completion: @escaping (Result<Void, Error>) -> Void)  {
        bookQueue.sync { [weak self] in
            guard let self = self else {
                completion(.failure(BookingError.UnableToBookSeat))
                return
            }
            
            guard let seat = self.seats.first (where: { seat in
                seat.seatId == seatId && seat.isOccupy
            }) else {
                completion(.failure(BookingError.UnableToBookSeat))
                return
            }
            seat.isOccupy = true
            completion(.success(()))
        }
    }
}

enum BookingError: Error {
    case UnableToBookSeat
}

class FlightSeat {
    
    var seatId: String
    var seatSize: SeatSize
    var isOccupy: Bool
    
    init(seatId: String, seatSize: SeatSize, isOccupy: Bool = false) {
        self.seatId = seatId
        self.seatSize = seatSize
        self.isOccupy = isOccupy
    }
    
}

enum SeatSize {
    case small
    case medium
    case large
}

class FlightSystem {
    private var flights: [Flight]
    init(flights: [Flight]) {
        self.flights = flights
    }
    
    func findAvailableSeat(flight: Flight, seatType: SeatSize) -> [FlightSeat] {
        let seats = flight.getAvailableSeats(seatSize: seatType)
        return seats
    }
    
    func bookFlight(flight: Flight, seatId: String, completion: @escaping (Result<Void, Error>) -> Void) {
        flight.bookSeat(seatId: seatId, completion: completion)
    }
    
}

func main() {
    
    let flight1 = Flight(seats: [
        FlightSeat(seatId: "A1", seatSize: .small),
        FlightSeat(seatId: "A2", seatSize: .medium),
        FlightSeat(seatId: "A3", seatSize: .large)
    ])
    
    let flight2 = Flight(seats: [
        FlightSeat(seatId: "B1", seatSize: .small),
        FlightSeat(seatId: "B2", seatSize: .medium),
        FlightSeat(seatId: "B3", seatSize: .large)
    ])
    
    let flightSystem = FlightSystem(flights: [flight1, flight2])
    let availableSeats = flightSystem.findAvailableSeat(flight: flight1, seatType: .small)
//    if let availableSeat = availableSeats.first {
//        flightSystem.bookFlight(flight: flight1, seatId: availableSeat.seatId)
//    }
    
    
    let dispatchGroup = DispatchGroup()
    let workerQueue = DispatchQueue(label: "bookFlight", attributes: .concurrent)
    
    for availableSeat in availableSeats {
        dispatchGroup.enter();
        workerQueue.async {
            flightSystem.bookFlight(flight: flight1, seatId: availableSeat.seatId) { result in
                switch result {
                case .success:
                    print("Booking successful for seat \(availableSeat.seatId) on flight \(flight1)")
                case .failure(let error):
                    print("Booking failed for seat \(availableSeat.seatId) on flight \(flight1) with error: \(error)")
                }
                dispatchGroup.leave()
            }
        }
    }
    
    dispatchGroup.wait()
//    dispatchGroup.notify(queue: DispatchQueue.main) {
//        print("All bookings completed.")
//    }

}

/*
func testConcurrentBooking() {
    let expectation = XCTestExpectation(description: "Concurrent booking test")
    let workerQueue = DispatchQueue(label: "testConcurrentBooking", attributes: .concurrent)
    for _ in 0..<10 {
        workerQueue.async {
            // Simulate concurrent booking attempts
            flight.bookSeat(seatId: "A1") { result in
                switch result {
                case .success:
                    XCTFail("Booking should have failed.")
                case .failure(let error):
                    XCTAssertEqual(error as? BookingError, BookingError.UnableToBookSeat)
                }
            }
        }
    }
    
    wait(for: [expectation], timeout: 5.0)
}

*/

// Handle Ambiguity
// Systemetic Approach


// 1. Requirements
//   The admin shall add/update flights
//   The customer shall book/cancel booking/search flights

// The user shall book a flight
// The user shall cancel a flight
// The user shall find an available seat of a flight with seat type
// The user shall book


// Abstract User -> Customer, Admin

// class Customer
// init(uuid, name)
// bookFlight(flight: Flight)


// class Admin: User
// init(uuid, name)


// class Flight
// id
// list of FlightSeat

// class FlightSeat
// seatId, seatSize

// enum SeatSize

// class FlightSystem
// list of flight
