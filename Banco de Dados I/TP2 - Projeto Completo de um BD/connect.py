import psycopg2, sys
from random import randint


class Personagem:
    def __init__(self, p_id, a_id, cursor):
        query = "SELECT id, nome, hp FROM rpg.personagem WHERE id = {0};".format(p_id)
        cursor.execute(query)
        result = cursor.fetchone()
        self.id, self.nome, self.hp = result

        query = "SELECT dano FROM rpg.arma WHERE id = {};".format(a_id)
        cursor.execute(query)
        result = cursor.fetchone()
        self.dano_arma = result[0]

    def __str__(self):
        return "Id: {}\n" \
               "Name: {}\n" \
               "Hp: {}".format(self.id, self.nome, self.hp)

    def setHP(self, valor):
        self.hp = valor


def batalha(p1: Personagem, p2: Personagem):
    turno = randint(1, 2)

    while p1.hp > 0 and p2.hp > 0:
        if turno == 1:
            atacante = p1
            defensor = p2
        elif turno == 2:
            atacante = p2
            defensor = p1

        defensor.setHP(0 if defensor.hp - atacante.dano_arma <= 0 else defensor.hp - atacante.dano_arma)
        print("{} sofreu um dano de {} pontos de vida e agora está com {}".format(
            defensor.nome, atacante.dano_arma, defensor.hp)
        )

        turno = randint(1, 2)

    if p1.hp > 0:
        print("{} venceu a batalha!".format(p1.nome))
    else:
        print("{} venceu a batalha!".format(p2.nome))


def connect(connect_str: str):
    try:
        # use our connection values to establish a connection
        conn = psycopg2.connect(connect_str)
        # create a psycopg2 cursor that can execute queries
        return conn
    except Exception as e:
        print("ERROR: Cannot connect to database", e)
        return None


if __name__ == '__main__':
    # 200.239.138.80
    conn = connect("dbname='{}' user='{}' host='localhost' password='{}'".format(sys.argv[1], sys.argv[2], sys.argv[3]))
    cursor = conn.cursor()

    cursor.execute("SELECT id, nome, hp, forca FROM rpg.personagem NATURAL JOIN rpg.jogador;")
    lista_jogadores = [j for j in cursor]

    cursor.execute("SELECT id, nome, dano, forca FROM rpg.item NATURAL JOIN rpg.arma;")
    lista_armas = [a for a in cursor]

    # Atualizando os HP's dos jogadores para o máximo possível

    for j in lista_jogadores:
        cursor.execute("SELECT hp_max FROM rpg.status NATURAL JOIN rpg.personagem WHERE id = {}".format(j[0]))
        hp_max = cursor.fetchone()[0]
        cursor.execute("UPDATE RPG.personagem SET hp = {} WHERE id = {};".format(hp_max, j[0]))

    # Exibindo informações ao usuário

    print("Lista de jogadores cadastrados (id, nome, vida, força):")
    for j in lista_jogadores:
        print("{}, {}, {}, {}".format(j[0], j[1], j[2], j[3]))

    print("\nLista de armas cadastradas (id, nome, dano, força requerida):")
    for a in lista_armas:
        print("{}, {}, {}, {}".format(a[0], a[1], a[2], a[3]))

    print("\n\n")

    done = False
    id_aj1 = id_j2 = id_aj1 = id_aj2 = None

    # Capturando informação do usuário

    id_j1 = int(input("Insira o id do 1º jogador: "))
    while not done:
        id_aj1 = int(input("Insira o id da arma do 1º jogador: "))
        jogador_selecionado = [j for j in lista_jogadores if j[0] == id_j1][0]
        arma_selecionada = [a for a in lista_armas if a[0] == id_aj1][0]

        if jogador_selecionado[3] < arma_selecionada[3]:
            print("{} não tem força necessária para usar a arma {}. Selecione outra arma!".format(
                jogador_selecionado[1], arma_selecionada[1])
            )
        else:
            done = True

    id_j2 = int(input("\nInsira o id do 2º jogador: "))
    done = False
    while not done:
        id_aj2 = int(input("Insira o id da arma do 2º jogador: "))
        jogador_selecionado = [j for j in lista_jogadores if j[0] == id_j2][0]
        arma_selecionada = [a for a in lista_armas if a[0] == id_aj2][0]

        if jogador_selecionado[3] < arma_selecionada[3]:
            print("{} não tem força necessária para usar a arma {}. Selecione outra arma!".format(
                jogador_selecionado[1], arma_selecionada[1])
            )
        else:
            done = True

    print("\nPreparem-se a batalha irá comecar!\n")

    p1 = Personagem(id_j1, id_aj1, cursor)
    p2 = Personagem(id_j2, id_aj2, cursor)

    batalha(p1, p2)

    conn.close()
