CREATE USER BCC321 PASSWORD 'bcc321-17.2';

DROP SCHEMA RPG CASCADE;

CREATE SCHEMA IF NOT EXISTS RPG;

GRANT ALL ON DATABASE RPGDB TO BCC321;

GRANT ALL ON ALL TABLES IN SCHEMA RPG TO BCC321;

----------------------------bcc321--------- PERSONAGEM --------------------------------

CREATE TABLE IF NOT EXISTS RPG.Status (
  id          SERIAL  NOT NULL,
  hp_max      INTEGER NOT NULL,
  mana_max    INTEGER NOT NULL,
  stamina_max INTEGER NOT NULL,
  capacidade  INTEGER NOT NULL,
  CONSTRAINT pkStatus PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Personagem (
  id        SERIAL      NOT NULL,
  nome      VARCHAR(15) NOT NULL UNIQUE,
  hp        INTEGER     NOT NULL,
  mana      INTEGER     NOT NULL,
  stamina   INTEGER     NOT NULL,
  ouro      INTEGER     NOT NULL,
  id_status SERIAL      NOT NULL, -- Foreign key
  CONSTRAINT pkPersonagem PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Jogador (
  id        SERIAL  NOT NULL, -- Foreign key
  xp        INTEGER NOT NULL,
  forca     INTEGER NOT NULL,
  id_nivel  SERIAL  NOT NULL, -- Foreign key
  id_guilda SERIAL,           -- Foreign key
  CONSTRAINT pkJogador PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Mob (
  id           SERIAL  NOT NULL, -- Foreign key
  xp_fornecido INTEGER NOT NULL,
  CONSTRAINT pkMob PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Npc (
  id        SERIAL  NOT NULL, -- Foreign key
  afinidade INTEGER NOT NULL,
  CONSTRAINT pkNpc PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Nivel (
  id           SERIAL  NOT NULL,
  xp_pxm_nivel INTEGER NOT NULL UNIQUE,
  CONSTRAINT pkNivel PRIMARY KEY (id)
);

------------------------------------ ITEM --------------------------------------

CREATE TABLE IF NOT EXISTS RPG.Item (
  id        SERIAL      NOT NULL,
  nome      VARCHAR(50) NOT NULL UNIQUE,
  preco     INTEGER     NOT NULL,
  peso      INTEGER     NOT NULL,
  descricao TEXT        NOT NULL,
  CONSTRAINT pkItem PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Arma (
  id           SERIAL  NOT NULL, -- Foreign key
  forca        INTEGER NOT NULL,
  durabilidade INTEGER NOT NULL,
  dano         INTEGER NOT NULL,
  CONSTRAINT pkArma PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Armadura (
  id     SERIAL  NOT NULL, -- Foreign key
  defesa INTEGER NOT NULL,
  CONSTRAINT pkArmadura PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.Consumivel (
  id      SERIAL  NOT NULL, -- Foreign key
  hp      INTEGER NOT NULL,
  mana    INTEGER NOT NULL,
  stamina INTEGER NOT NULL,
  CONSTRAINT pkConsumivel PRIMARY KEY (id)
);

------------------------------------ GUILDA ------------------------------------

CREATE TABLE IF NOT EXISTS RPG.Guilda (
  id           SERIAL      NOT NULL,
  nome         VARCHAR(15) NOT NULL UNIQUE,
  xp           INTEGER     NOT NULL,
  capacidade   INTEGER     NOT NULL,
  qtde_membros INTEGER     NOT NULL,
  id_nivel     SERIAL      NOT NULL, -- Foreign key
  CONSTRAINT pkGuilda PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS RPG.NivelGuilda (
  nivel        SERIAL  NOT NULL,
  xp_pxm_nivel INTEGER NOT NULL UNIQUE,
  CONSTRAINT pkNivelGuilda PRIMARY KEY (nivel)
);

----------------------- RELACIONAMENTOS MUITOS PARA MUITOS ---------------------

CREATE TABLE IF NOT EXISTS RPG.Utiliza (
  id_personagem SERIAL NOT NULL, -- Foreign key
  id_item       SERIAL NOT NULL, -- Foreign key
  CONSTRAINT fkUtiliza PRIMARY KEY (id_personagem, id_item)
);

CREATE TABLE IF NOT EXISTS RPG.Guerrilha (
  id_guilda_vencedora SERIAL  NOT NULL, -- Foreign key
  id_guilda_perdedora SERIAL  NOT NULL, -- Foreign key
  xp                  INTEGER NOT NULL,
  data                DATE    NOT NULL, -- Foreign key
  CONSTRAINT pkGuerrilha PRIMARY KEY (id_guilda_vencedora, id_guilda_perdedora, data)
);

CREATE TABLE IF NOT EXISTS RPG.GeraItem (
  id_jogador SERIAL NOT NULL, -- Foreign key
  id_mob     SERIAL NOT NULL, -- Foreign key
  id_item    SERIAL NOT NULL, -- Foreign key
  CONSTRAINT pkGeraItem PRIMARY KEY (id_jogador, id_mob, id_item)
);

-------------------- RESTRIÇÕES DE INTEGRIDADE REFERENCIAL ---------------------

ALTER TABLE RPG.Personagem
  ADD CONSTRAINT fkPersonagem_id_status FOREIGN KEY (id_status)
    REFERENCES RPG.Status (id) ON UPDATE CASCADE;

ALTER TABLE RPG.Jogador
  ADD CONSTRAINT fkJogador_id FOREIGN KEY (id)
    REFERENCES RPG.Personagem (id) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT fkJogador_id_nivel FOREIGN KEY (id_nivel)
    REFERENCES RPG.Nivel (id) ON UPDATE CASCADE,
  ADD CONSTRAINT fkJogador_id_guilda FOREIGN KEY (id_guilda)
    REFERENCES RPG.Guilda (id) ON UPDATE CASCADE ON DELETE SET NULL;

ALTER TABLE RPG.Mob
  ADD CONSTRAINT fkMob_id FOREIGN KEY (id)
    REFERENCES RPG.Personagem (id) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE RPG.Npc
  ADD CONSTRAINT fkNpc_id FOREIGN KEY (id)
    REFERENCES RPG.Personagem (id) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE RPG.Guilda
  ADD CONSTRAINT fkGuilda_id_nivel FOREIGN KEY (id_nivel)
    REFERENCES RPG.NivelGuilda (nivel) ON UPDATE CASCADE;

ALTER TABLE RPG.Utiliza
  ADD CONSTRAINT fkUtiliza_id_personagem FOREIGN KEY (id_personagem)
    REFERENCES RPG.Personagem (id) ON UPDATE CASCADE,
  ADD CONSTRAINT fkUtiliza_id_item FOREIGN KEY (id_item)
    REFERENCES RPG.Item (id) ON UPDATE CASCADE;

ALTER TABLE RPG.Guerrilha
  ADD CONSTRAINT fkUtiliza_id_guilda_vencedora FOREIGN KEY (id_guilda_vencedora)
    REFERENCES RPG.Guilda (id) ON UPDATE CASCADE,
  ADD CONSTRAINT fkUtiliza_id_guilda_perdedora FOREIGN KEY (id_guilda_perdedora)
    REFERENCES RPG.Guilda (id) ON UPDATE CASCADE;

ALTER TABLE RPG.GeraItem
  ADD CONSTRAINT fkGeraItem_id_jogador FOREIGN KEY (id_jogador)
    REFERENCES RPG.Jogador (id) ON UPDATE CASCADE,
  ADD CONSTRAINT fkGeraItem_id_mob FOREIGN KEY (id_mob)
    REFERENCES RPG.Mob (id) ON UPDATE CASCADE,
  ADD CONSTRAINT fkGeraItem_id_item FOREIGN KEY (id_item)
    REFERENCES RPG.Item (id) ON UPDATE CASCADE;

ALTER TABLE RPG.Arma
  ADD CONSTRAINT fkArma_id FOREIGN KEY (id)
    REFERENCES RPG.Item (id) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE RPG.Armadura
  ADD CONSTRAINT fkArmadura_id FOREIGN KEY (id)
    REFERENCES RPG.Item (id) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE RPG.Consumivel
  ADD CONSTRAINT fkConsumivel_id FOREIGN KEY (id)
    REFERENCES RPG.Item (id) ON DELETE CASCADE ON UPDATE CASCADE;

--------------------------------- INSERTIONS -----------------------------------

----------------------------------- ITEMS --------------------------------------
INSERT INTO RPG.Item (id, nome, preco, peso, descricao)
VALUES
  -------------------------------- POÇÕES --------------------------------------
  (1, 'Poção de cura pequena', 50, 1, 'Restaura 10 pontos de HP'),
  (2, 'Poção de cura média', 200, 1, 'Restaura 50 pontos de HP'),
  (3, 'Poção de cura grande', 500, 1, 'Restaura 200 pontos de HP'),
  (4, 'Poção de cura extrema', 5000, 1, 'Restaura todos os pontos de HP'),

  -------------------------------- ARMAS ---------------------------------------
  (5, 'Espada curta', 1000, 10, 'Espada inicial para o guerreiro'),
  (6, 'Machado de guerra', 1300, 15, 'Um machado que possui uma lâmina muito afiada');

INSERT INTO RPG.Consumivel (id, hp, mana, stamina)
VALUES
  -------------------------------- POÇÕES --------------------------------------
  (1, 10, 0, 0),
  (2, 50, 0, 0),
  (3, 200, 0, 0),
  (4, 999999999, 0, 0);

-------------------------------- ARMAS -----------------------------------------
INSERT INTO RPG.Arma (id, forca, durabilidade, dano)
VALUES
  (5, 5, 100, 30),
  (6, 10, 200, 50);

INSERT INTO RPG.Status (id, hp_max, mana_max, stamina_max, capacidade)
VALUES
  (1, 100, 100, 100, 100),
  (2, 150, 150, 150, 200);


---------------------------------- NIVEL ---------------------------------------

INSERT INTO RPG.Nivel (id, xp_pxm_nivel)
VALUES
  (1, 100);

--------------------------- PERSONAGEM / JOGADOR --------------------------------

INSERT INTO RPG.Personagem (id, nome, hp, mana, stamina, ouro, id_status)
VALUES
  (1, 'Jogador 1', 100, 100, 100, 0, 1),
  (2, 'Jogador 2', 150, 150, 1500, 0, 1);

ALTER TABLE RPG.Jogador ALTER COLUMN id_guilda DROP NOT NULL;

INSERT INTO RPG.Jogador(id, xp, forca, id_nivel, id_guilda)
VALUES
  (1, 0, 5, 1, NULL),
  (2, 0, 10, 1, NULL);

