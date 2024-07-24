import pygame
import torch
import random
import numpy as np
from collections import deque
from game import SnakeGameAI, Direction, Point
from model import Linear_QNet, QTrainer
import matplotlib.pyplot as plt
import time

MAX_MEMORY = 100_000
BATCH_SIZE = 1000
LR = 0.001

class Agent:

    def __init__(self):
        self.n_games = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)
        self.model = Linear_QNet(11, 256, 3)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)


    def get_state(self, game): # 11 trạng thái gồm: 3 trạng thái hướng di chuyển của rắn có va chạm với tường, 4 trạng thái biểu thị hướng di chuyển, 4 trạng thái biểu thị vị trí food, head
        head = game.snake[0]
        point_l = Point(head.x - 20, head.y)
        point_r = Point(head.x + 20, head.y)
        point_u = Point(head.x, head.y - 20)
        point_d = Point(head.x, head.y + 20)
        
        dir_l = game.direction == Direction.LEFT
        dir_r = game.direction == Direction.RIGHT
        dir_u = game.direction == Direction.UP
        dir_d = game.direction == Direction.DOWN

        state = [

            (dir_r and game.is_collision(point_r)) or
            (dir_l and game.is_collision(point_l)) or 
            (dir_u and game.is_collision(point_u)) or 
            (dir_d and game.is_collision(point_d)),

            (dir_u and game.is_collision(point_r)) or 
            (dir_d and game.is_collision(point_l)) or 
            (dir_l and game.is_collision(point_u)) or 
            (dir_r and game.is_collision(point_d)),

            (dir_d and game.is_collision(point_r)) or 
            (dir_u and game.is_collision(point_l)) or 
            (dir_r and game.is_collision(point_u)) or 
            (dir_l and game.is_collision(point_d)),

            dir_l,
            dir_r,
            dir_u,
            dir_d,

            game.food.x < game.head.x,  # food left
            game.food.x > game.head.x,  # food right
            game.food.y < game.head.y,  # food up
            game.food.y > game.head.y  # food down
            ]

        return np.array(state, dtype=int)

    def remember(self, state, action, reward, next_state, done): #lưu vào memory
        self.memory.append((state, action, reward, next_state, done))

    def train_long_memory(self): #huấn luyện dựa trên một batch mẫu lấy từ memory
        if len(self.memory) > BATCH_SIZE:
            mini_sample = random.sample(self.memory, BATCH_SIZE)
        else:
            mini_sample = self.memory

        states, actions, rewards, next_states, dones = zip(*mini_sample)
        self.trainer.train_step(states, actions, rewards, next_states, dones)

    def train_short_memory(self, state, action, reward, next_state, done): # huấn luyện dựa trên một mẫu đơn lẻ, khi batch mẫu chưa đủ độ lớn
        self.trainer.train_step(state, action, reward, next_state, done)

    def get_action(self, state):
        self.epsilon = 80 - self.n_games
        final_move = [0,0,0]
        if random.randint(0, 200) < self.epsilon:
            move = random.randint(0, 2)
            final_move[move] = 1
        else:
            state0 = torch.tensor(state, dtype=torch.float)
            prediction = self.model(state0) # tính toán tất cả giá trị Q của hành dộng ở state0
            move = torch.argmax(prediction).item() #chọn hành động có Q cao nhất
            final_move[move] = 1

        return final_move

    def get_action_model(self, state):

        final_move = [0,0,0]
        state0 = torch.tensor(state, dtype=torch.float)
        prediction = self.model(state0)
        move = torch.argmax(prediction).item()
        final_move[move] = 1

        return final_move

def train():
    plot_scores = []
    plot_mean_scores = []
    total_score = 0
    record = 0
    agent = Agent()
    game = SnakeGameAI()
    nums_episode = 300
    # try:
    #     model = Linear_QNet(11, 256, 3)
    #     model.load_state_dict(torch.load('model/model.pt'))
    #     agent.model = model
    #     with open("model/record.txt", "r") as f:
    #         record = int(f.read())
    #     print("Tiếp tục huấn luyện model!!")
    # except FileNotFoundError:
    #     print("Không tìm thấy model!! Huấn luyện lại từ đầu!!!")
    while True:
        done = False
        while not done:

            state_old = agent.get_state(game)
            final_move = agent.get_action(state_old)

            reward, done, score = game.play_step(final_move)
            state_new = agent.get_state(game)

            agent.train_short_memory(state_old, final_move, reward, state_new, done)
            agent.remember(state_old, final_move, reward, state_new, done)

            keys = pygame.key.get_pressed()
            if keys[pygame.K_q]:
                done = True
                time.sleep(0.5)

            if done:
                game.reset()
                agent.n_games += 1
                agent.train_long_memory()

                if score > record:
                    record = score
                    with open("model/record.txt","w") as f:
                        f.write(str(record))
                    torch.save(agent.model.state_dict(), 'model/model.pt')
                    print(agent.model.state_dict())

                print('Game', agent.n_games, 'Score', score, 'Record:', record)

                plot_scores.append(score)
                total_score += score
                mean_score = total_score / agent.n_games
                plot_mean_scores.append(mean_score)

    plt.plot(plot_scores)
    plt.plot(plot_mean_scores)
    plt.title('Training')
    plt.xlabel('episode')
    plt.ylabel('score')
    plt.savefig("Training.png")

if __name__ == '__main__':
    train()