CREATE TABLE CLIENT (
	siretClient		 int PRIMARY KEY,
	nomSociete		 char NOT NULL,
	nom_prenomClient char NOT NULL,
	adresseSociete	 char NOT NULL,
	telSociete		 char UNIQUE,
	mailSociete		 char NOT NULL,
	cpSociete		 char(5) NOT NULL,
	villeSociete	 char NOT NULL
);

CREATE TABLE FOURNISSEUR (
	siretFournisseur	int PRIMARY KEY,
	nomFournisseur		char NOT NULL,
	adresseFournisseur	char NOT NULL,
	telFournisseur		char,
	mailFournisseur		char NOT NULL,
	cpFournisseur		char(5) NOT NULL,
	villeFournisseur	char NOT NULL
);

CREATE TABLE CATEGORIE (numCategorie int PRIMARY KEY, nomCategorie char NOT NULL);

CREATE TABLE STATUT (numStatut int PRIMARY KEY, nomStatut char NOT NULL);

CREATE TABLE ARTICLE (
	numArticle		int PRIMARY KEY,
	nomArticle		char NOT NULL,
	categorie 		REFERENCES CATEGORIE,
	fournisseur		REFERENCES FOURNISSEUR,
	prixArticle		float NOT NULL CHECK(prixArticle > 0),
	descArticle		text,
	qteMin			int NOT NULL CHECK(qteMin >= 0),
	qteStock		int NOT NULL CHECK(qteStock >= qteMin)
);

CREATE TABLE COMMANDE (
	numCommande		int PRIMARY KEY,
	dateCommande	char(10) NOT NULL,
	dateEnvoi		char(10),
	dateReception	char(10),
	fraisLivraison	float NOT NULL CHECK(fraisLivraison >= 0),
	numStatut	 	REFERENCES STATUT,
	siretClient	 	REFERENCES CLIENT
);

CREATE TABLE LIGNE__COMMANDE (
	numCommande	REFERENCES COMMANDE,
	numArticle	REFERENCES ARTICLE,
	qteArticle	int NOT NULL CHECK(qteArticle > 0),
	PRIMARY KEY(numCommande, numArticle)
);

CREATE TABLE FACTURE (numFacture int PRIMARY KEY, dateFacture char(10), siretClient	REFERENCES CLIENT);