
import vk_api

session = vk_api.VkApi(token="")
vk = session.get_api()

def send_msg(_user_id):
    vk.messages.send(peer_id = _user_id, 
                    message = "Match is 1",
                    random_id = 0 )

send_msg(344092825)
