#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_SLOTS 10
#define MAX_VEHICLES 100

// Data structure for parking slots
typedef struct {
    int slotNumber;
    int distanceFromEntrance; // Priority based on distance
    int isOccupied;
    char vehicleNumber[20];
} ParkingSlot;

ParkingSlot slots[MAX_SLOTS];
int totalSlots = 0;

// Hash map-like structure for parked vehicles
char parkedVehicles[MAX_VEHICLES][20];
int vehicleToSlot[MAX_VEHICLES];
int vehicleCount = 0;

// Function to add a parking slot
void addSlot(int slotNumber, int distanceFromEntrance) {
    slots[totalSlots].slotNumber = slotNumber;
    slots[totalSlots].distanceFromEntrance = distanceFromEntrance;
    slots[totalSlots].isOccupied = 0; // Initially unoccupied
    totalSlots++;
}

// Function to find the nearest unoccupied slot
int findNearestSlot() {
    int nearestSlotIndex = -1;
    int minDistance = INT_MAX;

    for (int i = 0; i < totalSlots; i++) {
        if (!slots[i].isOccupied && slots[i].distanceFromEntrance < minDistance) {
            nearestSlotIndex = i;
            minDistance = slots[i].distanceFromEntrance;
        }
    }
    return nearestSlotIndex;
}

// Function to park a vehicle
void parkVehicle(char vehicleNumber[]) {
    int nearestSlotIndex = findNearestSlot();

    if (nearestSlotIndex == -1) {
        printf("No available slots for parking.\n");
        return;
    }

    // Allocate the nearest slot
    slots[nearestSlotIndex].isOccupied = 1;
    strcpy(slots[nearestSlotIndex].vehicleNumber, vehicleNumber);

    // Add vehicle to the hash map-like structure
    strcpy(parkedVehicles[vehicleCount], vehicleNumber);
    vehicleToSlot[vehicleCount] = nearestSlotIndex;
    vehicleCount++;

    printf("Vehicle %s parked in slot %d (distance: %d).\n", vehicleNumber, slots[nearestSlotIndex].slotNumber, slots[nearestSlotIndex].distanceFromEntrance);
}

// Function to unpark a vehicle
void unparkVehicle(char vehicleNumber[]) {
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(parkedVehicles[i], vehicleNumber) == 0) {
            int slotIndex = vehicleToSlot[i];
            slots[slotIndex].isOccupied = 0; // Free the slot
            printf("Vehicle %s removed from slot %d.\n", vehicleNumber, slots[slotIndex].slotNumber);

            // Remove from parked vehicles
            for (int j = i; j < vehicleCount - 1; j++) {
                strcpy(parkedVehicles[j], parkedVehicles[j + 1]);
                vehicleToSlot[j] = vehicleToSlot[j + 1];
            }
            vehicleCount--;
            return;
        }
    }
    printf("Vehicle %s not found in the parking lot.\n", vehicleNumber);
}

// Function to search for a parked vehicle
void searchVehicle(char vehicleNumber[]) {
    for (int i = 0; i < vehicleCount; i++) {
        if (strcmp(parkedVehicles[i], vehicleNumber) == 0) {
            int slotIndex = vehicleToSlot[i];
            printf("Vehicle %s is parked in slot %d.\n", vehicleNumber, slots[slotIndex].slotNumber);
            return;
        }
    }
    printf("Vehicle %s not found in the parking lot.\n", vehicleNumber);
}

int main() {
    int choice;
    char vehicleNumber[20];
    int slotNumber, distance;

    printf("Smart Parking System Initialized.\n\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Parking Slot\n");
        printf("2. Park Vehicle\n");
        printf("3. Remove Vehicle\n");
        printf("4. Search Vehicle\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter slot number and distance from entrance: ");
                scanf("%d %d", &slotNumber, &distance);
                addSlot(slotNumber, distance);
                printf("Slot %d added with distance %d.\n", slotNumber, distance);
                break;

            case 2:
                printf("Enter vehicle number to park: ");
                scanf("%s", vehicleNumber);
                parkVehicle(vehicleNumber);
                break;

            case 3:
                printf("Enter vehicle number to remove: ");
                scanf("%s", vehicleNumber);
                unparkVehicle(vehicleNumber);
                break;

            case 4:
                printf("Enter vehicle number to search: ");
                scanf("%s", vehicleNumber);
                searchVehicle(vehicleNumber);
                break;

            case 5:
                printf("Exiting Smart Parking System.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
