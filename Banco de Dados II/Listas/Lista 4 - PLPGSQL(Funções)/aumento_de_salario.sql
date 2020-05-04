CREATE OR REPLACE FUNCTION aumento_de_salario(depto Departamento.NomeDepto%TYPE, percentual real) RETURNS integer AS $$
DECLARE 
    reg RECORD;
BEGIN
    SELECT INTO reg * FROM Departamento WHERE NomeDepto = depto;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Departamento % não encontrado', depto;
    ELSE
        FOR reg IN SELECT * FROM funcionario WHERE ID_Depto = reg.ID_Depto ORDER BY NomeFunc LOOP
            reg.Salario = reg.Salario + reg.Salario*(percentual/100.0);
			UPDATE Funcionario
			SET Salario = reg.Salario
			WHERE reg.ID_Func = ID_Func;
        END LOOP;
        RETURN 0;
    END IF;
END;
$$ LANGUAGE plpgsql;
