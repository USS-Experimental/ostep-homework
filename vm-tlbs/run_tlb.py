import subprocess
import sys

# Insure the args are correct
if len(sys.argv) != 3:
    print("Usage: python3 run_tlb.py <pagelimit> <times>")
    sys.exit(1)

# Get the pagesize of the os
pagesize = subprocess.run(['getconf', 'PAGE_SIZE'], capture_output=True, text=True).stdout.strip()
pagenum = 1
pagelimit = int(sys.argv[1])
times = sys.argv[2]

# Print argvs
print("Start TLB size measurement")
print("Page size: " + pagesize)
print("Page limit: " + str(pagelimit))
print("Loop times: " + times)

x_data = []
result = []

while pagenum <= pagelimit:
    
    # Run tlb.out to get timecost
    timecost = subprocess.run(['taskset', '-c', '0', './tlb.out', pagesize, str(pagenum), times],
                               capture_output=True, text=True).stdout.strip()
    
    # Print result
    print("Visit " + str(pagenum) + ' pages,' + " Time cost: " + str(timecost) + "ns")

    # Check typecasting timecost to float number
    try:
        timecost = float(timecost)
    except ValueError:
        print(f"Unable to cast '{timecost}' to a float.")
        sys.exit(1)

    # Save data
    x_data.append(pagenum)
    result.append(timecost)

    # Double the page bumber
    pagenum *= 2

print("TLB size measurement complete")

def makeplot():
    # Draw plot of result
    fig, ax = plt.subplots()
    ax.plot(x_data, result, marker='o', color='orange', linestyle='-', linewidth=2, markersize=8)

    # Setup laber
    ax.set_title('TLB Size Measurement')
    ax.set_xlabel('Number Of Pages')
    ax.set_ylabel('Time Per Access (ns)')

    # Setup x axis
    ax.set_xscale('log')
    ax.set_xticks(x_data)
    ax.set_xticklabels([str(x) for x in x_data])

    # Save plot
    plt.savefig('result.png')

try:
    import matplotlib.pyplot as plt
    makeplot()
    print("Plotting complete")
except ImportError:
    print("No matplotlib, unable to plotting")