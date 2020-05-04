CREATE OR REPLACE FUNCTION encontrar_departamento(func Funcionario.NomeFunc%TYPE) RETURNS text AS $$
DECLARE
	reg RECORD; reg1 Funcionario.ID_Func%TYPE; depto Funcionario.ID_Depto%TYPE;
BEGIN
	SELECT INTO reg1 ID_Func FROM Funcionario WHERE NomeFunc = func; 
	SELECT INTO reg * FROM Funcionario WHERE Funcionario.ID_Func = reg1;
	IF NOT FOUND THEN
		RAISE EXCEPTION 'Empregado % não encontrado', func;
	ELSE
		depto := reg.ID_Depto;
		SELECT INTO reg * FROM Departamento WHERE ID_Depto = depto;
		RETURN reg.ID_Depto || '---' || reg.NomeDepto;
	END IF;
END;
$$ LANGUAGE plpgsql;