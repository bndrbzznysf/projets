--1) Afficher le nom, l'adresse e-mail et le numéro de téléphone des fournisseurs de l'entreprise 
-- Cela permet de contacter les fournisseurs s'il est nécessaire de passer commande pour réapprovisionner le stock
SELECT nomFournisseur, mailFournisseur, telFournisseur FROM fournisseur;


--2) Afficher les noms, prix et descriptions des produits proposés par l'entreprise ainsi que leur catégorie
-- cela permet de voir le catalogue d'articles disponibles pour les clients
SELECT nomArticle, nomCategorie, prixArticle, descArticle 
FROM ARTICLE A 
INNER JOIN CATEGORIE C ON A.categorie = C.numCategorie;


--3) Afficher le nom et le prix des extrudeuses manuelles proposées par l'entreprise
-- cela permet de visualiser les extrudeuses 
SELECT nomArticle, prixArticle
FROM ARTICLE A
INNER JOIN categorie C ON C.numCategorie=A.categorie
WHERE nomCategorie = 'extrudeuses manuelles';


--4) Afficher le nom et l'adresse mail des clients dont les commandes sont en cours de préparation
-- cela permet d'avoir les coordonnées des clients afin de les contacter pour les prévenir de l'avancée de leur commande
SELECT nom_prenomClient, mailSociete
FROM CLIENT CL
INNER JOIN COMMANDE CM ON CL.siretClient = CM.siretClient 
INNER JOIN STATUT S ON S.numStatut = C.numStatut --CM.numStatut (problème d'alias)
WHERE nomStatut='en cours de préparation';


--5) Afficher le nom des clients ayant effectué le plus de commande, ainsi que leur nombre de commandes
-- cela permet d'analyser les commandes effectuées par client
SELECT nom_prenomClient, COUNT(CL.siretClient) AS nbCommandes
FROM CLIENT CL
INNER JOIN COMMANDE C ON CL.siretClient = C.siretClient
GROUP BY nom_prenomClient, CL.siretClient
ORDER BY nbCommandes DESC;


--6) Calculer le coût total des produits vendus par l'entreprise
-- cela permet de prévoir en avance le coût d'import de matériel
SELECT nomCategorie, SUM(prixArticle) AS prixTotal
FROM ARTICLE A 
INNER JOIN CATEGORIE C ON A.categorie=C.numcategorie
GROUP BY nomCategorie;


--7) Afficher le nom des clients dont les commandes sont en attente, ainsi que le numéro des commandes
-- cela permet de connaître les commandes à confirmer restantes afin de les préparer
SELECT numCommande
FROM CLIENT CL
INNER JOIN COMMANDE C ON CL.siretClient = C.siretClient
INNER JOIN STATUT S ON S.numStatut = C.numStatut
WHERE nomStatut='en attente';


--8) Afficher les produits dont le stock doit bientôt être refait
-- cela permet de prévoir les articles à réapprovisionner
SELECT nomArticle
FROM ARTICLE
WHERE qteStock-10 < qteMin;


--9) Afficher le nombre de produits importés par chaque fournisseur
-- cela permet de comparer pour chaque fournisseur le nombre de produits importés
SELECT F.nomFournisseur, COUNT(numArticle) AS nbArticles
FROM FOURNISSEUR F
INNER JOIN ARTICLE A ON A.fournisseur = F.siretFournisseur
GROUP BY A.fournisseur;


--10) Afficher le prix moyen des produits pour chaque catégorie d'articles
-- cela permet de faire des statistiques sur le prix de vente des articles
SELECT nomCategorie, ROUND(AVG(prixArticle), 2) AS prixMoyen
FROM ARTICLE A
INNER JOIN CATEGORIE C ON A.categorie = C.numCategorie
GROUP BY nomCategorie; --il manquait un point-virgule...


--11) Afficher pour chaque client le montant total des dépenses de leurs commandes
-- cela permet de faire une analyse des ventes
SELECT nom_prenomClient, SUM(prixArticle*qteArticle+fraisLivraison) AS tarifClient
FROM CLIENT CL
INNER JOIN COMMANDE C ON CL.siretClient=C.siretClient
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle = LC.numArticle
GROUP BY nom_prenomClient, CL.siretClient
ORDER BY tarifClient DESC;


--12) Afficher la liste des clients n'ayant pas encore passé commande
-- cela permet de les contacter afin de les inciter à passer commande / leur proposer des réductions pour leur premier achat
SELECT nom_prenomClient
FROM CLIENT CL
LEFT JOIN COMMANDE C ON CL.siretClient = C.siretClient
WHERE C.siretClient IS NULL;


--13) Afficher les clients ayant commandé des KIT BACHE ENERGY HT1600 WELDY, ainsi que leur numéro de commande
-- cela permet de faire des statistiques sur la vente du produit
SELECT nom_prenomClient, C.numCommande
FROM CLIENT CL
INNER JOIN COMMANDE C ON CL.siretClient=C.siretClient
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle = LC.numArticle
WHERE nomArticle='KIT BACHE ENERGY HT1600 WELDY';


--14) Afficher la quantité totale de produits en stock par catégorie d'articles
-- cela permet d'analyser la quantité de produits disponibles pour chaque catégorie
SELECT nomCategorie, SUM(qteStock) AS stocks
FROM ARTICLE A 
INNER JOIN CATEGORIE C ON A.categorie=C.numcategorie
GROUP BY nomCategorie;


--15) Calculer le coût total de vente de tous les produits pour chaque fournisseur
-- cela permet de prévoir le coût d'importation pour chaque fournisseur
SELECT F.nomFournisseur, SUM(prixArticle) AS nbArticles
FROM FOURNISSEUR F
INNER JOIN ARTICLE A ON A.fournisseur = F.siretFournisseur
GROUP BY A.fournisseur;


--16) Afficher le nombre total de produits par commande pour chaque client
-- cela permet de faire des statistiques sur les commandes des clients
SELECT nom_prenomClient, SUM(qteArticle) AS tarifClient
FROM CLIENT CL
INNER JOIN COMMANDE C ON CL.siretClient=C.siretClient
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle = LC.numArticle
GROUP BY nom_prenomClient, CL.siretClient;


--17) Afficher le nom des clients ayant effectué des commandes au mois de mars
-- cela permet de faire des statistiques sur les commandes des clients
SELECT DISTINCT nom_prenomClientlk
FROM COMMANDE C
INNER JOIN CLIENT CL ON CL.siretClient = C.siretClient
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle=LC.numArticle
INNER JOIN STATUT S ON S.numStatut = C.numStatut
WHERE SUBSTR(dateCommande, 4, 2)='03' AND nomStatut != 'annulée';


--18) Afficher les produits les plus chers par catégorie
-- cela permet d'analyser les prix des articles
SELECT nomCategorie, MAX(prixArticle) AS prixMax
FROM ARTICLE A 
INNER JOIN CATEGORIE C ON A.categorie=C.numcategorie
GROUP BY nomCategorie;


--19) Afficher le total des ventes par mois
-- cela permet d'analyser les ventes de l'entreprise
SELECT SUBSTR(dateCommande, 4, 2) AS mois, SUM(prixArticle) AS totalVentes
FROM COMMANDE C
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle=LC.numArticle
WHERE numStatut!=2
GROUP BY SUBSTR(dateCommande, 4, 2);


-- 20) Calculer le bénéfice réalisé par l'entreprise durant le mois de juillet
-- cela permet d'analyser le résultat des ventes de l'entreprise
SELECT SUM(qteArticle*prixArticle+fraisLivraison) AS benefice
FROM COMMANDE C
INNER JOIN LIGNE__COMMANDE LC ON C.numCommande=LC.numCommande
INNER JOIN ARTICLE A ON A.numArticle=LC.numArticle
INNER JOIN STATUT S ON S.numStatut = C.numStatut
WHERE SUBSTR(dateCommande, 4, 2)='07' AND nomStatut!='annulée';