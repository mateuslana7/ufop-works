#include "Endereco.h"

string Endereco::getRua() 
{ 
	return rua; 
}

void Endereco::setRua(string r)
{ 
	rua = r; 
}

string Endereco::getBairro() 
{ 
	return bairro; 
}

void Endereco::setBairro(string b)
{
	bairro = b;
}

string Endereco::getNomeLugar() 
{ 
	return nomeLugar; 
}

void Endereco::setNomeLugar(string nome) 
{ 
	nomeLugar = nome; 
}

string Endereco::getCidade() 
{ 
	return cidade; 
}

void Endereco::setCidade(string c) 
{ 
	cidade = c; 
}

int Endereco::getNumero() 
{ 
	return numero; 
}

void Endereco::setNumero(int n) 
{ 
	numero = n; 
}