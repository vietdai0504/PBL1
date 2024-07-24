import matplotlib.pyplot as plt

# Define the network structure
input_layer = 3
hidden_layer = 4
output_layer = 2

# Define node positions
input_nodes = [i for i in range(input_layer)]
hidden_nodes = [i + input_layer for i in range(hidden_layer)]
output_nodes = [i + input_layer + hidden_layer for i in range(output_layer)]

# Draw connections
for i in input_nodes:
    for j in hidden_nodes:
        plt.plot([i, j], [0, 1], 'k-', linewidth=1)

for i in hidden_nodes:
    for j in output_nodes:
        plt.plot([i, j], [1, 2], 'k-', linewidth=1)

# Draw nodes
plt.scatter(input_nodes, [0] * input_layer, s=500, c='blue')
plt.scatter(hidden_nodes, [1] * hidden_layer, s=500, c='red')
plt.scatter(output_nodes, [2] * output_layer, s=500, c='green')

# Set labels and title
plt.xlabel("Nodes")
plt.ylabel("Layers")
plt.title("Simple Neural Network")

# Display the plot
plt.show()