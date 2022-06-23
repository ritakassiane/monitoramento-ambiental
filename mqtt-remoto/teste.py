import json
msg_count = 24
msg = f"messages:{msg_count}"
valor = msg.split(':')[1]
print(valor)
temperatura = {
        'temperatura':f'{valor}'
}
print(json.dumps(temperatura))