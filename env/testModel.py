import time

import pygame
import torch
from game import SnakeGameAI
from agent import Agent
from model import Linear_QNet


def play():
    model = Linear_QNet(11,256,3)
    game = SnakeGameAI()
    agent = Agent()
    model.load_state_dict(torch.load("model/model.pt"))
    agent.model = model
    game.reset()

    while True:
        keys = pygame.key.get_pressed()
        state = agent.get_state(game)
        action = agent.get_action_model(state)

        reward, done, score = game.play_step(action)

        if keys[pygame.K_q]:
            done = True
            time.sleep(0.5)
        if done:
            game.reset()
            print(f"Score - {score}")

if __name__ == '__main__':
    play()