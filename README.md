# ViperPing

<div align="center">
  <img src="assets/logo.png" alt="ViperPing Logo" width="250"/>
  
  **Interactive Terminal-Based Network Connectivity Monitor**
  
  [![License](https://img.shields.io/badge/license-GPL--3.0-blue)](LICENSE)
  [![GitHub Stars](https://img.shields.io/github/stars/Fest1on/ViperPing)](https://github.com/Fest1on/ViperPing)
  [![Contributors](https://img.shields.io/github/contributors/Fest1on/ViperPing)](https://github.com/Fest1on/ViperPing/graphs/contributors)
</div>

---

## 📖 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [User Interface](#user-interface)
- [Controls](#controls)
- [Configuration](#configuration)
- [Examples](#examples)
- [Performance](#performance)
- [Architecture](#architecture)
- [Contributing](#contributing)
- [License](#license)
- [Support](#support)

---

## 🎯 Overview

ViperPing is a high-performance, interactive terminal-based network diagnostic tool designed for real-time monitoring of host availability and network latency. With a rich console UI, ViperPing provides instant visual feedback on network health, making it ideal for infrastructure monitoring, network troubleshooting, and continuous connectivity analysis.

Whether you're managing servers, debugging network issues, or performing live network monitoring, ViperPing delivers accurate metrics with an intuitive, interactive interface.

### Key Highlights

- **Interactive Console UI**: Real-time visual feedback with dynamic updates
- **Lightning-Fast Performance**: Optimized for minimal latency and maximum throughput
- **Live Statistics**: Instant min/max/avg response time calculations
- **Scalable Architecture**: Monitor hundreds of hosts simultaneously
- **Production-Ready**: Battle-tested reliability for critical infrastructure

---

## ✨ Features

### Core Capabilities

| Feature | Description |
|---------|-------------|
| **Interactive UI** | Rich terminal interface with live updates and navigation |
| **Multi-Host Monitoring** | Simultaneously monitor multiple targets with real-time stats |
| **ICMP & TCP Support** | Multiple protocol options for different network scenarios |
| **Packet Loss Detection** | Real-time detection and visual indication of connectivity issues |
| **Response Time Analysis** | Min, max, average, and percentile latency calculations |
| **Live Statistics** | Continuously updated metrics displayed in the console |
| **Color-Coded Results** | Visual indicators for host status (online/offline/warning) |
| **DNS Resolution** | Built-in DNS lookup with caching for performance |

### Advanced Features

- **Batch Host Management**: Add and manage multiple targets from the UI
- **Alert System**: Visual and audio alerts when latency exceeds thresholds
- **Historical Data**: Track connectivity trends over monitoring sessions
- **Customizable Intervals**: Adjust ping rates on-the-fly from the interface
- **IPv4 & IPv6 Support**: Full compatibility with both IP versions
- **Concurrent Execution**: Parallel processing for improved responsiveness
- **Retry Logic**: Automatic retry mechanisms with configurable backoff
- **Keyboard Navigation**: Efficient control with intuitive keybindings

---

## 🚀 Installation

### Prerequisites

- **OS**: Linux, macOS, or Windows (with WSL)
- **Terminal**: Modern terminal emulator (supports ANSI colors)
- **Memory**: Minimum 256MB RAM
- **Network**: Active internet connection for remote hosts

### From Source

```bash
# Clone the repository
git clone https://github.com/Fest1on/ViperPing.git
cd ViperPing

# Install dependencies
[your-package-manager] install

# Build the project
[build-command]

# Run ViperPing
./viper-ping

