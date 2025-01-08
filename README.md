# Mini_Projects_using_C++
Mini Projects Using C++

1. ATM MACHINE
2. DIGITAL CLOCK

-------------------------------------------------------------------------------------------------------------------------------------------------------

# Modern ATM & Digital Clock Applications

This repository contains two C++ applications: a feature-rich ATM simulation system and a real-time digital clock. Both applications demonstrate various C++ programming concepts and provide interactive user interfaces.

## 1. Modern ATM System

### Overview
The ATM simulation system is a comprehensive console-based application that mimics real ATM functionality with advanced security features and user-friendly interface.

### Key Features
- 🔐 Secure PIN authentication system
- 💰 Multiple transaction types
- 📝 Transaction history tracking
- ⚡ Fast cash options
- 🔒 Account security with lockout mechanism
- 💳 Multi-bank support

### Technical Implementation

#### Core Components

1. **Account Structure**
   - Stores user data including:
     - Card number
     - PIN
     - Balance
     - Bank name
     - Account holder name
     - Transaction history
     - Security-related fields (failed attempts, lock status)

2. **ATM Class**
   ```cpp
   class ATM {
       private:
           map<char, Account> accounts;
           const int MAX_FAILED_ATTEMPTS = 3;
           const int LOCK_DURATION_MINUTES = 60;
           // ... private methods
       public:
           // ... public interface
   };
   ```

#### Security Features
- PIN validation with retry limits
- Account lockout system (60-minute lockout after 3 failed attempts)
- Transaction logging with timestamps
- Masked card number display

#### Available Operations
1. **Withdraw Money**
   - PIN verification
   - Balance verification
   - Transaction logging

2. **Balance Check**
   - Secure balance display
   - Transaction logging

3. **Transaction History**
   - Chronological list of transactions
   - Timestamp-based logging

4. **Fast Cash**
   - Preset withdrawal amounts
   - Quick access to common denominations

5. **PIN Change**
   - Current PIN verification
   - New PIN confirmation
   - Length validation

### Usage
```bash
# Compile the ATM application
g++ ATM_MACHINE.cpp -o atm

# Run the application
./atm

# Available test accounts:
- Card 'k': PIN 1234 (SBI Bank)
- Card 's': PIN 5678 (HDFC Bank)
- Card 'l': PIN 9123 (ICICI Bank)
- Card 'i': PIN 4567 (AXIS Bank)
- Card 'n': PIN 8912 (PNB Bank)
```

## 2. Digital Clock

### Overview
A real-time digital clock application that displays the current time and date with format switching capabilities.

### Key Features
- ⏰ Real-time updates
- 📅 Date display
- 🔄 12/24 hour format toggle
- 🖥️ Clean console interface

### Technical Implementation

#### Core Components

1. **DigitalClock Class**
   ```cpp
   class DigitalClock {
       private:
           bool is24HourFormat;
           bool isRunning;
           // ... private methods
       public:
           DigitalClock();
           void run();
   };
   ```

#### Key Functions

1. **Time Display**
   - Uses `chrono` and `ctime` for accurate time management
   - Formats time and date with proper padding
   - Updates every second

2. **Format Toggle**
   - Switches between 12/24 hour format
   - Handles AM/PM indication
   - Maintains time accuracy during format changes

3. **User Interface**
   - Clear screen implementation for different platforms
   - Non-blocking input handling
   - Continuous display updates

### Usage
```bash
# Compile the Digital Clock application
g++ DIGITAL_CLOCK.cpp -o clock

# Run the application
./clock

# Controls:
- Press 'F' to toggle between 12/24 hour format
- Press 'Q' to quit the application
```

## Technical Dependencies

Both applications require:
- C++11 or higher
- Standard C++ libraries
- A C++ compiler (g++ recommended)

### Common Libraries Used
- `<iostream>` - For input/output operations
- `<string>` - String manipulation
- `<chrono>` - Time management
- `<thread>` - Threading operations
- `<iomanip>` - Output formatting

## Building and Running

### Prerequisites
- C++ compiler (g++ recommended)
- Make (optional)

### Compilation Commands
```bash
# ATM System
g++ ATM_MACHINE.cpp -o atm -std=c++11

# Digital Clock
g++ DIGITAL_CLOCK.cpp -o clock -std=c++11
```

## Code Structure

### ATM System
- Modular class design
- Separation of concerns between UI and business logic
- Robust error handling
- Transaction logging system

### Digital Clock
- Single-responsibility principle
- Non-blocking input handling
- Platform-independent screen clearing
- Real-time updates

## Contributing
Feel free to fork this repository and submit pull requests. You can also open issues for bugs or feature requests.
