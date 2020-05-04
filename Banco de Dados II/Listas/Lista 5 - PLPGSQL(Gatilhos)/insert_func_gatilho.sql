CREATE TABLE CadastroFuncionario(
	ID_Func     NUMERIC(4)     NOT NULL,
	NomeFunc	VARCHAR(30)  NOT NULL,
	DataInsercao	DATE	NOT NULL,
	CONSTRAINT pk_cadastrofunc PRIMARY KEY (ID_Func)
);

CREATE OR REPLACE FUNCTION func_gatilho() RETURNS trigger AS $$
DECLARE 
	reg RECORD;
BEGIN
	IF NEW.ID_Func IS NULL THEN
	RAISE EXCEPTION 'ID do funcionario nulo';
	END IF;
	SELECT INTO reg ID_Func FROM Funcionario WHERE ID_Func = NEW.ID_Func;
	IF FOUND THEN
	RAISE EXCEPTION 'ID do funcionario ja existe';
	END IF;
	
	IF NEW.NomeFunc IS NULL THEN
	RAISE EXCEPTION 'Nome do empregado nulo';
	END IF;
	
	IF NEW.Endereco IS NULL THEN
	RAISE EXCEPTION 'Endereco do empregado nulo';
	END IF;
	
	IF NEW.DataNasc IS NULL THEN
	RAISE EXCEPTION 'Data de nascimento do empregado nulo';
	END IF;
	
	IF NEW.Sexo IS NULL THEN
	RAISE EXCEPTION 'Sexo do empregado nulo';
	END IF;
	
	IF NEW.Salario IS NULL THEN
	RAISE EXCEPTION 'Salário nulo de %', NEW.NomeFunc;
	END IF;
	IF NEW.Salario < 0 THEN
	RAISE EXCEPTION 'Salário negativo de %', NEW.NomeFunc;
	END IF;
	
	SELECT INTO reg ID_Func FROM Funcionario WHERE ID_Func = NEW.ID_Superv AND NEW.ID_Superv != NEW.ID_Func;	
	IF NOT FOUND THEN
	RAISE EXCEPTION 'ID de supervisor invalido';
	END IF;
	
	IF NEW.ID_Depto IS NULL THEN
	RAISE EXCEPTION 'Nome do departamento nulo';
	END IF;
	
	-- REGISTRA A ALTERACAO
	INSERT INTO CadastroFuncionario SELECT NEW.ID_Func, current_user, 'now';
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER func_gatilho BEFORE INSERT ON Funcionario FOR EACH ROW EXECUTE PROCEDURE 
func_gatilho();