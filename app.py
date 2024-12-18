import streamlit as st

# Data structures for parking slots and vehicles
MAX_SLOTS = 10
MAX_VEHICLES = 100

# Parking slot class
class ParkingSlot:
    def __init__(self, slot_number, distance_from_entrance):
        self.slot_number = slot_number
        self.distance_from_entrance = distance_from_entrance
        self.is_occupied = False
        self.vehicle_number = ""

# Initialize global data
slots = []
parked_vehicles = []
vehicle_to_slot = []
vehicle_count = 0

# Function to add a parking slot
def add_slot(slot_number, distance_from_entrance):
    if len(slots) < MAX_SLOTS:
        new_slot = ParkingSlot(slot_number, distance_from_entrance)
        slots.append(new_slot)
        return f"Slot {slot_number} added with distance {distance_from_entrance}."
    else:
        return "Max slot limit reached."

# Function to find the nearest unoccupied slot
def find_nearest_slot():
    min_distance = float('inf')
    nearest_slot_index = -1
    for i, slot in enumerate(slots):
        if not slot.is_occupied and slot.distance_from_entrance < min_distance:
            nearest_slot_index = i
            min_distance = slot.distance_from_entrance
    return nearest_slot_index

# Function to park a vehicle
def park_vehicle(vehicle_number):
    nearest_slot_index = find_nearest_slot()
    if nearest_slot_index == -1:
        return "No available slots for parking."
    
    slot = slots[nearest_slot_index]
    slot.is_occupied = True
    slot.vehicle_number = vehicle_number
    parked_vehicles.append(vehicle_number)
    vehicle_to_slot.append(nearest_slot_index)
    return f"Vehicle {vehicle_number} parked in slot {slot.slot_number} (distance: {slot.distance_from_entrance})."

# Function to unpark a vehicle
def unpark_vehicle(vehicle_number):
    if vehicle_number in parked_vehicles:
        index = parked_vehicles.index(vehicle_number)
        slot_index = vehicle_to_slot[index]
        slot = slots[slot_index]
        slot.is_occupied = False
        slot.vehicle_number = ""
        parked_vehicles.pop(index)
        vehicle_to_slot.pop(index)
        return f"Vehicle {vehicle_number} removed from slot {slot.slot_number}."
    else:
        return f"Vehicle {vehicle_number} not found in the parking lot."

# Function to search for a parked vehicle
def search_vehicle(vehicle_number):
    if vehicle_number in parked_vehicles:
        index = parked_vehicles.index(vehicle_number)
        slot_index = vehicle_to_slot[index]
        slot = slots[slot_index]
        return f"Vehicle {vehicle_number} is parked in slot {slot.slot_number}."
    else:
        return f"Vehicle {vehicle_number} not found in the parking lot."

# Streamlit UI
st.title("Smart Parking System")

menu = ["Add Parking Slot", "Park Vehicle", "Remove Vehicle", "Search Vehicle"]
choice = st.sidebar.selectbox("Select an option", menu)

if choice == "Add Parking Slot":
    st.subheader("Add a Parking Slot")
    slot_number = st.number_input("Enter Slot Number", min_value=1)
    distance = st.number_input("Enter Distance from Entrance", min_value=0)
    
    if st.button("Add Slot"):
        message = add_slot(slot_number, distance)
        st.success(message)

elif choice == "Park Vehicle":
    st.subheader("Park a Vehicle")
    vehicle_number = st.text_input("Enter Vehicle Number")
    
    if st.button("Park Vehicle"):
        if vehicle_number:
            message = park_vehicle(vehicle_number)
            st.success(message)
        else:
            st.error("Please enter a valid vehicle number.")

elif choice == "Remove Vehicle":
    st.subheader("Remove a Vehicle")
    vehicle_number = st.text_input("Enter Vehicle Number")
    
    if st.button("Remove Vehicle"):
        if vehicle_number:
            message = unpark_vehicle(vehicle_number)
            st.success(message)
        else:
            st.error("Please enter a valid vehicle number.")

elif choice == "Search Vehicle":
    st.subheader("Search for a Vehicle")
    vehicle_number = st.text_input("Enter Vehicle Number")
    
    if st.button("Search Vehicle"):
        if vehicle_number:
            message = search_vehicle(vehicle_number)
            st.success(message)
        else:
            st.error("Please enter a valid vehicle number.")

# Display the current status of parking slots
st.subheader("Parking Slot Status")
if len(slots) > 0:
    for slot in slots:
        status = "Occupied" if slot.is_occupied else "Available"
        st.write(f"Slot {slot.slot_number}: {status} (Distance: {slot.distance_from_entrance})")
else:
    st.write("No parking slots available.")
