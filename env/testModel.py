import time
import matplotlib.pyplot as plt
import pygame
import torch
from game import SnakeGameAI
from agent import Agent
from model import Linear_QNet

list_score = []
list_avg_score = []
def play():
    model = Linear_QNet(11,256,3)
    game = SnakeGameAI()
    agent = Agent()
    model.load_state_dict(torch.load("model/model.pt"))
    agent.model = model
    game.reset()
    nums_episode = 100

    while nums_episode > 0:
        keys = pygame.key.get_pressed()
        state = agent.get_state(game)
        action = agent.get_action_model(state)

        reward, done, score = game.play_step(action)

        if keys[pygame.K_q]:
            done = True
            time.sleep(0.5)
        if done:
            nums_episode -= 1
            list_score.append(score)
            list_avg_score.append(score/len(list_score))
            game.reset()
            print(f"Score - {score}")
    plt.plot(list_score)
    plt.plot(list_avg_score)
    plt.title("After Train")
    plt.xlabel("Episode")
    plt.ylabel("Score")
    plt.savefig("aftertrain.png")

if __name__ == '__main__':
    play()