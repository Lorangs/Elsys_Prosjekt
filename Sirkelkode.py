from flask import Flask, request
import matplotlib.pyplot as plt
import threading
import time
from matplotlib.animation import FuncAnimation

app = Flask(__name__)

# Initialize list to store sensor data
sensor_data_list = []
lock = threading.Lock()

def plot_data_thread():
    fig, ax = plt.subplots()
    ax.set_xlim(-1, 1)
    ax.set_ylim(-1, 1)
    circle = plt.Circle((-0.9, 0), 0.1, color='red', alpha=0.5)
    ax.add_artist(circle)

    def update_circle(frame):
        nonlocal circle
        with lock:
            if sensor_data_list:
                new_x = min(circle.center[0] + 0.01, 0.9)  # Move circle upward by 0.01 each time
                circle.set_center((new_x, circle.center[1]))
        return circle,

    ani = FuncAnimation(fig, update_circle, frames=None, blit=True)
    plt.show()

def plot_data():
    threading.Thread(target=plot_data_thread, daemon=True).start()

@app.route('/receiver_path', methods=['POST'])
def receive_data():
    global sensor_data_list
    sensor_data = float(request.form['data'])
    print("Received sensor data:", sensor_data)
    
    # Add sensor data to the list
    with lock:
        sensor_data_list.append(sensor_data)
        # Limit the list to store only the last 20 values
        sensor_data_list = sensor_data_list[-20:]
    
    return 'Data received successfully'

if __name__ == '__main__':
    plot_data()  # Start the plot thread
    app.run(host='0.0.0.0', port=5000)