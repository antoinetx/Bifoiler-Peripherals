#!/usr/bin/env python3
"""
Plots the output from the arduino sensor.
"""

import argparse
import pandas as pd
import matplotlib.pyplot as plt


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "file", help="CSV output from arduino", type=argparse.FileType())
    parser.add_argument(
        "--output",
        "-o",
        help="Save the plot to given file instead of showing it.")

    return parser.parse_args()


def main():
    args = parse_args()

    df = pd.read_csv(args.file, header=0)

    df['Current'] = df['current_ma'] * 1e-3
    df['Voltage'] = df['voltage_mv'] * 1e-3
    df['Time'] = df['time_ms'] * 1e-3

    ax = df.plot('Time', 'Current')
    ax2 = df.plot('Time', 'Voltage', secondary_y=True, ax=ax)

    ax.set_xlabel('Time [s]')
    ax.set_ylabel('Current [A]')
    ax2.set_ylabel('Voltage [V]')

    if args.output:
        plt.savefig(args.output)
    else:
        plt.show()


if __name__ == '__main__':
    main()
