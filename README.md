# SA-MP Advanced Airdrop Event System

<p align="center">
  <img src="https://i.imgur.com/YOUR_IMAGE_HERE.png" alt="Airdrop System" width="600">
</p>

## 📋 Descrição

Sistema profissional de eventos Airdrop para servidores SA-MP. Este sistema permite que administradores iniciem eventos de Airdrop em qualquer localização do mapa, criando uma zona de combate onde jogadores podem competir para coletar armas e itens especiais.

## ✨ Funcionalidades

- Criação de eventos Airdrop em qualquer localização do mapa
- Animação realista de queda do Airdrop do céu
- Zona de perigo demarcada com GangZone vermelha
- Notificação para jogadores ao entrar na zona de perigo
- Sistema de coleta com timer de 60 segundos
- Recompensa de armas para o jogador que coletar o Airdrop
- Ícone no mapa para localizar o Airdrop
- Texto 3D informativo sobre o Airdrop
- Sistema de iteração eficiente para gerenciar jogadores coletando o Airdrop

## 🛠️ Instalação

### Como Gamemode Independente

1. Baixe o arquivo `AirdropSystem.pwn`
2. Coloque-o na pasta `gamemodes` do seu servidor
3. Compile o arquivo usando o compilador Pawn
4. Adicione `AirdropSystem` ao seu arquivo `server.cfg` na linha `gamemode0`
5. Certifique-se de ter todas as dependências instaladas (veja abaixo)

### Adaptação para Gamemode Existente

1. Abra o arquivo `AirdropSystem.pwn` e copie as seguintes seções para o seu gamemode:
   - Definições (#define)
   - Enumerações (enum E_AIRDROP_DATA)
   - Variáveis globais (ServerAirdrop, Player_AirDropTimer, Iterator:PlayerAirDrop)
   - Declarações de funções (forward)
   - Todas as funções das seções HOOKS, COMANDOS, STOCKS e PUBLICS

2. Adicione as chamadas para as seguintes funções nos callbacks correspondentes do seu gamemode:
   ```pawn
   // Em OnPlayerDisconnect
   if(IsPlayerCollectAidrop(playerid))
       IsPlayerRemoveCollect(playerid);
   
   // Em OnPlayerEnterDynamicArea
   if(areaid == ServerAirdrop[E_AIRDROP_AREA])
   {
       SendClientMessage(playerid, 0xFF0000FF,"AIRDROP: Voce entrou em uma zona de perigo!");
   }
   ```

3. Certifique-se de que seu gamemode inclui todas as dependências necessárias:
   ```pawn
   #include <a_samp>
   #include <streamer>
   #include <Pawn.CMD>
   #include <YSI_Coding\y_hooks>
   #include <YSI_Data\y_iterate>
   ```

## 📦 Dependências

Este sistema requer as seguintes dependências:

### Streamer Plugin v2.9.6 v1.0.0
- Download: [GitHub - samp-incognito/samp-streamer-plugin](https://github.com/samp-incognito/samp-streamer-plugin/releases)
- Instalação: Coloque os arquivos `streamer.dll` (Windows) ou `streamer.so` (Linux) na pasta `plugins` do seu servidor
- Adicione `streamer` à linha `plugins` no seu arquivo `server.cfg`

### YSI-Includes
- Download: [GitHub - pawn-lang/YSI-Includes](https://github.com/pawn-lang/YSI-Includes)
- Instalação: Extraia os arquivos para a pasta `pawno/include` do seu servidor

### Pawn.CMD 3.4.0
- Download: [GitHub - katursis/Pawn.CMD](https://github.com/katursis/Pawn.CMD/releases)
- Instalação: Coloque os arquivos `pawncmd.dll` (Windows) ou `pawncmd.so` (Linux) na pasta `plugins` do seu servidor
- Coloque o arquivo `Pawn.CMD.inc` na pasta `pawno/include` do seu servidor
- Adicione `pawncmd` à linha `plugins` no seu arquivo `server.cfg`

## 🔧 Configuração

Você pode configurar o sistema editando os seguintes valores no início do arquivo:

```pawn
#define AIRDROP_OBJECTS_COUNT 2       // Número de objetos usados no Airdrop
static const Float:E_AIRDROP_SPEED = 2.0;  // Velocidade de queda do Airdrop
```

Para modificar a recompensa do Airdrop, edite a função `OnTimerCollectAirdrop`:

```pawn
GivePlayerWeapon(playerid, 31, 150);  // Dá ao jogador uma M4 com 150 munições
```

## 📝 Comandos

- `/Airdrop` - Inicia um evento de Airdrop na posição atual do jogador (apenas para administradores)
- `/pAirdrop` - Coleta o Airdrop (deve estar próximo ao Airdrop e dentro da zona de perigo)

## 👨‍💻 Desenvolvido por

- MARINHO
- GitHub: [eykMarinho](https://github.com/eykMarinho)
- YouTube: [@eykMarinho](https://www.youtube.com/@eykMarinho)

## 🚀 Otimização e Boas Práticas

O sistema foi desenvolvido com foco em otimização e desempenho. Aqui estão algumas características de otimização implementadas:

1. **Uso de static**: Todas as variáveis e funções são declaradas como `static` para reduzir o tamanho do AMX e melhorar o desempenho.

2. **Uso de Iteradores**: O sistema utiliza o iterador `PlayerAirDrop` para gerenciar apenas os jogadores que estão coletando o Airdrop, evitando loops desnecessários por todos os jogadores.

3. **Verificação de Proximidade Eficiente**: A função `IsPlayerInAirdrop()` utiliza um raio de verificação de 2.0 unidades para determinar se o jogador está próximo ao Airdrop.

4. **Limpeza de Recursos**: O sistema limpa corretamente todos os recursos (objetos, áreas, zonas, etc.) quando o Airdrop é coletado ou destruído.

5. **Uso de Hooks YSI**: O sistema utiliza hooks do YSI para callbacks como OnPlayerDisconnect e OnPlayerEnterDynamicArea, permitindo uma integração mais limpa com outros sistemas.

6. **Operadores Ternários**: Funções como `IsPlayerCollectAidrop()` utilizam operadores ternários para verificações rápidas e eficientes.

7. **Estrutura de Dados Otimizada**: A enumeração `E_AIRDROP_DATA` organiza todos os dados relacionados ao Airdrop em uma única estrutura, facilitando o gerenciamento e acesso.

## 📄 Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.