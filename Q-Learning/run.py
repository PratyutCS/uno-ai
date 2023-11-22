import os
import pandas as pd
import numpy as np

from src.agents import QLearningAgent
from src.game import tournament, Game1
import config as conf

def main():

    run = tournament(
        iterations = conf.params['iterations'],
        algo       = conf.params['algorithm'],
        comment    = conf.params['logging'],
        agent_info = conf.params['model']
    )

    result = pd.concat([
        pd.Series(run[0], name='winner'), 
        pd.Series(run[1], name='turns')
    ], axis = 1)
    
    result["win_rate"] = np.where(result["winner"]==conf.player_name_1,1,0)
    result["win_rate"] = result["win_rate"].cumsum()/(result.index+1)

    q_vals = pd.DataFrame(run[2].q)
    q_vals.index.rename("id", inplace=True)

    if not os.path.exists("assets"):
        os.makedirs("assets")

    q_vals.to_csv("assets/q-values.csv", index=True)
    result.to_csv("assets/results.csv", index=False) 
    

def play():
    global agent, algorithm
    algorithm = conf.params['algorithm']
    agent = QLearningAgent(conf.params['model'])
    game = Game1(
                player_1_name=conf.player_name_1, 
                player_2_name=conf.player_name_2,
                starting_name=conf.player_name_2,
                agent=agent,
                algorithm=conf.params['algorithm'],
                comment=conf.params['logging']
            )


if __name__ == "__main__":
    main()
    while True:
        if(int(input("Enter 1 to break else Enter anything else to continue : ")) == 1):
            break
        play()