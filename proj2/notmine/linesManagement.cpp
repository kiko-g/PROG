#include "myTypes.h"

/*
Recebe os par�metros do utilizador (ID da linha, frequ�ncia de circula��o, paragens e dura��es) e guarda-os numa nova
struct, que � adicionada ao vetor criado anteriormente.
*/
void createLine(vector<Line> &data)
{
	Line lineStruct;
	data.push_back(lineStruct);
	int id, frequency;
	int verify = -1;
	int i = 1;
	int j = 0;
	bool validInput = false;
	string stop;

	cout << "Criar linha" << endl << endl;

	//Colocar o ID numa nova struct, tendo em conta o input v�lido/inv�lido.

	while (!validInput)
	{
		cout << "Identificador da linha: ";
		if (cin >> id && id>0)
		{
			verify = searchLineIdentifier(id, data);

			if (id > 1000)
			{
				cin.ignore(1000, '\n');
				cout << "Insira um ID com, no m�ximo, 3 d�gitos." << endl;
			}

			else if (verify == -1)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.ignore(1000, '\n');
				cout << "Esse identificador j� existe! Tente novamente..." << endl;
			}

		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		}
	}

	data[data.size() - 1].idNumber = id;

	//Colocar a frequ�ncia na nova struct, tendo em conta o input v�lido/inv�lido.

	validInput = false;
	while (!validInput)
	{
		cout << "Frequ�ncia: ";
		if (cin >> frequency && frequency>0)
			{	
				validInput = true;
				cin.ignore(1000, '\n');
			}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		}
	}

	data[data.size() - 1].frequency = frequency;

	/*
	Colocar as paragens na nova struct. Deteta o fim do input e tamb�m assegura que o input � v�lido, na medida
	em que n�o permite input vazio
	*/

	while (!cin.eof())
		{
			validInput = false;

			while (!validInput)
			{
				cout << "Paragem " << i << " (CTRL-Z para terminar): ";
				getline(cin, stop);

				if (cin.eof() && i <= 2)
				{
					cout << "Por favor, insira mais paragens." << endl;
					cin.clear();
				}
				else if (cin.eof())
					break;
				else if (stop == "") //N�o aceita input vazio.
					cout << "Input inv�lido! Tente novamente..." << endl << endl; 
				else
					validInput = true;
			}

			if (cin.eof())
			{
				cin.clear();
				break;
			}

			data[data.size() - 1].stopsList.push_back(stop);
			i++;
		}
		
	//Colocar as dura��es na nova struct, verificando a validade do input.

	int numberOfIterations = data[data.size() - 1].stopsList.size() - 1;

	while (j < numberOfIterations)
	{
		int d;

		validInput = false;

		while(!validInput)
		{
			cout << "Dura��o " << (j+1) << ": ";
			if (cin >> d && d>0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl << endl;
			}
		}

		j++;

		data[data.size() - 1].timesBetweenStops.push_back(d);
	}

	cout << "Linha adicionada com sucesso!" << endl;
}

/*
Edita as linhas j� criadas. Fornece meios para: alterar a frequ�ncia de circula�ao, adicionar paragem, remover paragem,
alterar paragem, 
*/
void editLine(vector<Line> &data)
{
	int id, userChoice;
	int verify = -1;
	bool validInput = false;

	cout << "Alterar linha" << endl << endl;

	while (!validInput)
	{
		cout << "Identificador da linha: ";
		if (cin >> id && id>0)
		{
			verify = searchLineIdentifier(id, data);

			if (verify != -1)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.ignore(1000, '\n');
				cout << "Esse identificador n�o existe! Tente novamente..." << endl << endl;
			}

		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		}
	}
	
	//Apresenta uma interface com as fun��es dispon�veis para alterar uma linha

	cout << endl << "Escolha o que pretende alterar" << endl;
	cout << "1 - Alterar frequ�ncia" << endl;
	cout << "2 - Adicionar paragem" << endl;
	cout << "3 - Alterar paragem" << endl;
	cout << "4 - Remover paragem" << endl;
	cout << "5 - Alterar dura��o" << endl << endl;

	userChoice = verifyInput(1, 5);

	clearScreen();

	if (userChoice == 1)
		changeFrequency(id, data);
	else if (userChoice == 2)
		addStop(id, data);
	else if (userChoice == 3)
		changeStop(id, data);
	else if (userChoice == 4)
		removeStop(id, data);
	else if (userChoice == 5)
		changeDuration(id, data);
}

/*
Recebe do utilizador um identificador para uma linha, e caso ela exista remove-a do vetor de structs. 
*/
void removeLine(vector<Line> &data)
{
	int id;
	int verify = -1;
	bool validInput = false;

	cout << "Remover linha" << endl << endl;

	while (!validInput)
	{
		cout << "Identificador da linha: ";
		if (cin >> id && id>0)
		{
			verify = searchLineIdentifier(id, data);

			if (verify != -1)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.ignore(1000, '\n');
				cout << "Esse identificador n�o existe! Tente novamente..." << endl << endl;
			}

		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		}
	}

	data.erase(data.begin() + verify);

	cout << "Linha apagada com sucesso!" << endl;
}

/*
Muda a frequ�ncia de circula��o numa linha dada pelo utilizador.
*/
void changeFrequency(int id, vector<Line> &data)
{
	int index, newfreq;	
	index = searchLineIdentifier(id, data);
	bool validInput = false;

	cout << "Alterar frequ�ncia" << endl;

	cout << endl << "A frequ�ncia atual �: " << data[index].frequency << endl;

	

	while (!validInput)
	{
		cout << "Nova frequ�ncia: ";
		if (cin >> newfreq && newfreq>0)
		{
				validInput = true;
				cin.ignore(1000, '\n');
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		}
	}

	data[index].frequency = newfreq;

	cout << "Altera��es efetuadas com sucesso!" << endl;
}

/*
Remove uma paragem numa linha dada pelo utilizador, assegurando que � corrigida a dura��o.
Para isso, pergunta ao utilizador qual a dura��o entre as duas paragens adjacentes � paragem removida.
*/
void removeStop(int id, vector<Line> &data)
{
	int index;
	string stop;
	int stopIndex=-1;
	bool validInput = false;

	index = searchLineIdentifier(id, data);

	cout << "Remover paragem" << endl;

	cout << endl << "Atualmente, a linha tem as seguintes paragens: ";
	for (int i = 0; i < data[index].stopsList.size(); i++)
	{
		if (i > 0)
			cout << " - ";
		cout << data[index].stopsList[i];
	}

	//Procura o indice da paragem e remove-a do vetor de strings da sua respetiva struct

	while (!validInput)
	{
		cout << endl << "Paragem a remover: ";
		getline(cin, stop);

		for (int i = 0; i < data[index].stopsList.size(); i++)
			if (data[index].stopsList[i] == stop)
				stopIndex = i;

		if (stopIndex > -1)
			validInput = true;
		else
			cout << "A paragem especificada n�o existe! Tente novamente..." << endl;
	}

	data[index].stopsList.erase(data[index].stopsList.begin() + stopIndex);

	//Corrige as dura��es

	if (stopIndex == 0)
	{
		data[index].timesBetweenStops.erase(data[index].timesBetweenStops.begin() + stopIndex);
		cout << "Paragem removida com sucesso!" << endl;
	}
	else if (stopIndex == data[index].stopsList.size())
	{
		data[index].timesBetweenStops.erase(data[index].timesBetweenStops.begin() + stopIndex - 1);
		cout << "Paragem removida com sucesso!" << endl;
	}
	else
	{
		int indexStop1, indexStop2, newDuration;

		indexStop1 = stopIndex - 1;
		indexStop2 = stopIndex;
		
		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << data[index].stopsList[indexStop1] << " e " << data[index].stopsList[indexStop2] << ": ";

			if (cin >> newDuration && newDuration > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops.erase(data[index].timesBetweenStops.begin() + indexStop1);

		data[index].timesBetweenStops[indexStop1] = newDuration;

		cout << "Paragem removida com sucesso!" << endl;
	}
}

/*
Adiciona uma paragem a uma linha indicada pelo utilizador, assegurando que as dura��es s�o corrigidas.
*/
void addStop(int id, vector<Line> &data)
{
	int index, stopIndex;
	string stop;
	bool validInput = false;

	index = searchLineIdentifier(id, data);

	cout << "Adicionar paragem" <<  endl;

	cout << endl << "Atualmente, a linha tem as seguintes paragens: ";
	for (int i = 0; i < data[index].stopsList.size(); i++)
	{
		if (i > 0)
			cout << " - ";
		cout << data[index].stopsList[i];
	}

	while (!validInput)
	{
		cout << endl << "Paragem a adicionar: ";
		getline(cin, stop);

		if(stop=="")
			cout << "Input inv�lido! Tente novamente..." << endl;
		else if (searchStop3(data,index,stop))
			cout << "A paragem j� se encontra na linha! Tente novamente..." << endl;
		else
			validInput = true;
	}
	
	validInput = false;

	while (!validInput)
	{
		cout << "�ndice (a come�ar em 0): ";

		if (cin >> stopIndex)
		{
			if (stopIndex >= 0 && stopIndex <= data[index].stopsList.size())
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.ignore(1000, '\n');
				cout << "Esse �ndice n�o existe! Tente novamente..." << endl;
			}
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente..." << endl;
		}
	}

	data[index].stopsList.insert(data[index].stopsList.begin() + stopIndex, stop);

	//Corrigir dura��es

	if (stopIndex == 0)
	{
		int duration;

		validInput = false;

		while (!validInput)
		{
			cout << "Dura��o entre " << stop << " e " << data[index].stopsList[stopIndex + 1] << ": ";
			
			if (cin >> duration && duration > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops.insert(data[index].timesBetweenStops.begin(), duration);
	}
	else if (stopIndex == (data[index].stopsList.size() - 1))
	{
		int duration;

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << data[index].stopsList[stopIndex - 1] << " e " << stop << ": ";

			if (cin >> duration && duration > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops.insert(data[index].timesBetweenStops.begin() + stopIndex-1, duration);
	}
	else
	{
		int duration1, duration2;

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << data[index].stopsList[stopIndex - 1] << " e " << stop << ": ";

			if (cin >> duration1 && duration1 > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << stop << " e " << data[index].stopsList[stopIndex + 1] << ": ";

			if (cin >> duration2 && duration2 > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops[stopIndex - 1] = duration1;

		data[index].timesBetweenStops.insert(data[index].timesBetweenStops.begin() + stopIndex, duration2);
	}

	cout << "Paragem adicionada com sucesso!" << endl;

}

/*
Altera uma paragem numa linha dada pelo utilizador, assegurando que as dura��es s�o corrigidas.
*/
void changeStop(int id, vector<Line> &data)
{
	string stop, newStop;
	int index, stopIndex=-1;
	bool validInput = false;

	index = searchLineIdentifier(id, data);

	cout << "Alterar paragem" << endl;

	cout << endl << "Atualmente, a linha tem as seguintes paragens: ";
	for (int i = 0; i < data[index].stopsList.size(); i++)
	{
		if (i > 0)
			cout << " - ";
		cout << data[index].stopsList[i];
	}

	while (!validInput)
	{
		cout << endl << "Paragem a alterar: ";
		getline(cin, stop);

		for (int i = 0; i < data[index].stopsList.size(); i++)
			if (data[index].stopsList[i] == stop)
				stopIndex = i;

		if (stopIndex != -1)
			validInput = true;
		else
			cout << "A paragem especificada n�o existe! Tente novamente..." << endl;
	}

	validInput = false;
	while (!validInput)
	{
		cout << "Nova paragem: ";
		getline(cin, newStop);

		if (stop == "")
			cout << "Input inv�lido! Tente novamente..." << endl << endl;
		else
			validInput = true;
	}

	data[index].stopsList[stopIndex] = newStop;

	//Corrigir as dura��es

	if (stopIndex == 0)
	{
		int duration;

		validInput = false;

		while (!validInput)
		{
			cout << "Dura��o entre " << newStop << " e " << data[index].stopsList[stopIndex + 1] << ": ";

			if (cin >> duration && duration > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops[stopIndex] = duration;
	}
	else if (stopIndex == data[index].stopsList.size() - 1)
	{
		int duration;

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << data[index].stopsList[stopIndex - 1] << " e " << newStop << ": ";

			if (cin >> duration && duration > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops[stopIndex - 1] = duration;
	}
	else
	{
		int duration1, duration2;

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << data[index].stopsList[stopIndex - 1] << " e " << newStop << ": ";

			if (cin >> duration1 && duration1 > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		validInput = false;
		while (!validInput)
		{
			cout << "Dura��o entre " << newStop << " e " << data[index].stopsList[stopIndex + 1] << ": ";

			if (cin >> duration2 && duration2 > 0)
			{
				validInput = true;
				cin.ignore(1000, '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input inv�lido! Tente novamente..." << endl;
			}
		}

		data[index].timesBetweenStops[stopIndex - 1] = duration1;

		data[index].timesBetweenStops[stopIndex] = duration2;
	}

	cout << "Paragem alterada com sucesso!" << endl;
}

/*
Altera a dura��o de um percurso especificado pelo utilizador. � �til para casos em que, por exemplo, um dos percursos se
encontre em obras e seja necess�rio efetuar uma altera��o.
*/
void changeDuration(int id, vector<Line> &data)
{
	bool validInput=false;
	int index, index1 = -1, index2 = -1, oldDuration, newDuration;
	string stop1, stop2;

	index = searchLineIdentifier(id, data);

	cout << "Alterar dura��o" << endl << endl;

	while (!validInput)
	{
		index1 = -1; 
		index2 = -1;

		cout << "Paragem 1: ";
		getline(cin, stop1);

		cout << "Paragem 2: ";
		getline(cin, stop2);

		for (int i = 0; i < data[index].stopsList.size(); i++)
		{
			if (data[index].stopsList[i] == stop1)
				index1 = i;
			if (data[index].stopsList[i] == stop2)
				index2 = i;
		}

		if (index1 != -1 && index2 != -1)
		{
			if (index1 == index2 + 1 || index2 == index1 + 1)
				validInput = true;
			else
				cout << "As paragens devem ser consecutivas. Tente novamente..." << endl;		
		}
		else
			cout << "As paragens n�o foram encontradas! Tente novamente..." << endl;
	}

	cout << "Atualmente, a dura��o entre " << stop1 << " e " << stop2 << " �: ";

	oldDuration = data[index].timesBetweenStops[min(index1,index2)];
	cout << oldDuration << endl;

	validInput = false;
	while (!validInput)
	{
		cout << "Nova dura��o: ";
		
		if (cin >> newDuration)
		{
			if (newDuration > 0)
				if (newDuration != oldDuration)
					validInput = true;
				else
				{
					cout << "A dura��o � a mesma! Tente novamente...";
					cin.ignore(1000, '\n');
				}
			else
			{
				cout << "Introduza um valor maior. Tente novamente...";
				cin.ignore(1000, '\n');
			}
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input inv�lido! Tente novamente...";
		}
					
		}

	data[index].timesBetweenStops[min(index1,index2)] = newDuration;

	cout << "Altera��es efetuadas com sucesso!" << endl;
 }
